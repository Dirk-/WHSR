
#include "WHSR.h"

// For copy & paste
#if defined(ARDUINO_AVR_NANO)
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

#define SWITCH_ADC_PULLUP D11  // D11, Pin 14, BINT
#define SWITCH_PIN A2               // A2 = D16 = ADC[2], BUT

// switchInterruptState lifecycle (separate from SWITCH_INTERRUPT_STATE hardware flag in WHSR.h)
#define SWITCH_PRESS_NONE        0  // No press detected
#define SWITCH_PRESS_WAIT        1  // ISR fired, ADC read pending (Nano 33 BLE)
#define SWITCH_PRESS_READY       2  // ADC read done, value available for sketch
#define SWITCH_PRESS_DONE        3  // Value consumed by sketch
// Das ist nicht das gleiche wie switchInterruptState:
volatile unsigned char switchInterruptAktiv = SWITCH_PRESS_NONE;
volatile unsigned char warDrin = 0;

//
// Initialisiert die Kollisionserkennung
//
void WHSR::initSwitches(void)
{
    // Switch-Messschaltung aktivieren
	pinMode(SWITCH_ADC_PULLUP, OUTPUT);
	digitalWrite(SWITCH_ADC_PULLUP, LOW);
}

//
// Liest die Taster für die Kollisionserkennung aus
//
unsigned char WHSR::readSwitches(void)
{
	DebugSerial_print("readSwitches() war drin: ");
    DebugSerial_println(warDrin);
	if(switchInterruptAktiv == SWITCH_PRESS_READY)
	{
		switchInterruptAktiv = SWITCH_PRESS_DONE;
		return switchValue;
	}
#if defined(ARDUINO_AVR_NANO)
	else
	{
    DoCheckADCMode(SWITCH_ADC);
	long adcValue = mySensorValues[SWITCH_ADC];
	adcValue = adcValue == 0 ? 1 : adcValue; // Don't divide by zero
    return (unsigned char)(((10160000L / adcValue - 10000L) * SwitchFactor + 5000L) / 10000);
	}
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    if(switchInterruptAktiv == SWITCH_PRESS_WAIT)
    {
        // ISR already set D11 LOW; just wait for settling and read.
        delay(2);
        long adcValue = analogRead(SWITCH_PIN);
    DebugSerial_print("SWITCH_ADC Interrupt: ");
    DebugSerial_println(adcValue);
        adcValue = adcValue == 0 ? 1 : adcValue;
        switchValue = (unsigned char)(((10160000L / adcValue - 10000L) * SwitchFactor + 5000L) / 10000);
        switchInterruptAktiv = SWITCH_PRESS_READY;
        switchInterruptOn(NULL, FALLING); // re-arm: sets D11 HIGH and re-attaches interrupt (same as AVR)
		switchInterruptAktiv = SWITCH_PRESS_DONE;
        return switchValue;
    }

    // Direct polling read (interrupt mode not active)
	long adcValue = analogRead(SWITCH_PIN); // use pin constant, not channel index
    DebugSerial_print("SWITCH_ADC ohne Interrupt: ");
    DebugSerial_println(adcValue);
	adcValue = adcValue == 0 ? 1 : adcValue; // Don't divide by zero
	switchInterruptAktiv = SWITCH_PRESS_DONE;
    return (unsigned char)(((10160000L / adcValue - 10000L) * SwitchFactor + 5000L) / 10000);
#endif
}

//
// Turn On the PinChange Interrupt
//
void WHSR::switchInterruptOn(void (*isrfunction)(), PinStatus triggerOn)
{
    // Messschaltung deaktivieren, SWITCH_PIN wird zum digitalen Eingang
	digitalWrite(SWITCH_ADC_PULLUP, HIGH);
	delay(2);

#if defined(ARDUINO_AVR_NANO)
    byte pin = SWITCH_PIN;
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
// Interrupt for switches
// Use INPUT (no internal pullup): SWITCH_ADC_PULLUP (D11) already provides external pullup to A2.
// Adding INPUT_PULLUP would lower the effective pullup impedance and prevent
// high-resistance switches from pulling A2 below the LOW threshold.
    DebugSerial_println("attachInterrupt");
    pinMode(SWITCH_PIN, INPUT);
    if(isrfunction == NULL) {
        DebugSerial_println("Using default switchISR");
        isrfunction = switchISR;
    } else {
        DebugSerial_println("Using custom switchISR");
    }
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), isrfunction, triggerOn);
#endif

    switchInterruptAktiv = SWITCH_PRESS_NONE;
    switchInterruptState = SWITCH_INTERRUPT_IDLE;
}

//
// Turn Off the PinChange Interrupt
//
void WHSR::switchInterruptOff(void)
{
    // Messschaltung aktivieren, SWITCH_PIN wird zum analogen Eingang
	digitalWrite(SWITCH_ADC_PULLUP, LOW);
	delay(2);

#if defined(ARDUINO_AVR_NANO)
    byte pin = SWITCH_PIN;
    PCICR  &= ~bit (digitalPinToPCICRbit(pin)); // disable interrupt for the group
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    detachInterrupt(digitalPinToInterrupt(SWITCH_PIN));
#endif

    switchInterruptAktiv = SWITCH_PRESS_NONE;
    switchInterruptState = SWITCH_INTERRUPT_NONE;
}

//
//	Return true if Switch was pressed
//
bool WHSR::switchAvailable()
{
#if defined(ARDUINO_ARDUINO_NANO33BLE)
    // PRESS_WAIT: ISR fired, readSwitches() still needs to do the ADC read
    // PRESS_READY: ADC read done, value is waiting for the sketch
    return switchInterruptAktiv == SWITCH_PRESS_WAIT || switchInterruptAktiv == SWITCH_PRESS_READY;
#else
	return switchInterruptAktiv == SWITCH_PRESS_READY;
#endif
}

//
// Pin Change Interrupt Service Routine
//
void WHSR::switchInterruptSeviceRoutine(void)
{
    // Interrupts sind deaktiviert beim Eintritt in ISR

    // - On release (DONE + pin HIGH): reset state
	if(switchInterruptAktiv == SWITCH_PRESS_DONE && digitalRead(SWITCH_PIN) == HIGH)
	{
		switchInterruptAktiv = SWITCH_PRESS_NONE;
		return; 
	}
	
	if(switchInterruptAktiv != SWITCH_PRESS_NONE ||		// Wenn schon einmal ein Button gedrückt wurde oder
	   digitalRead(SWITCH_PIN) == HIGH)	// wenn kein Button gedrückt wurde
		return;

#if defined(ARDUINO_ARDUINO_NANO33BLE)
    // Mirror AVR behaviour as closely as possible:
    // - On press: immediately disable interrupt and set D11 LOW (measurement mode),
    //   then flag PRESS_WAIT so readSwitches() does the ADC read from main-loop context
    //   (analogRead/delay are not safe in ISR context).
    // detachInterrupt() and digitalWrite() are safe to call from ISR context on mbed.
    detachInterrupt(digitalPinToInterrupt(SWITCH_PIN)); // disable, same as AVR switchInterruptOff()
    digitalWrite(SWITCH_ADC_PULLUP, LOW);               // switch to measurement mode
    switchInterruptAktiv = SWITCH_PRESS_WAIT;
#else
	
	switchInterruptAktiv = SWITCH_PRESS_WAIT;
	noInterrupts();
	
    // Ausschalten, damit der analoge Wert gelesen werden kann
	switchInterruptOff();

	switchValue = 0;
	//unsigned long startMillis = millis(); //Aktuellen Zeitstempel speichern
	//while (switchValue == 0 && (millis() - startMillis < 1000)) 
		switchValue = readSwitches();

    // Wieder einschalten
	switchInterruptOn(NULL, FALLING); // re-arm: sets D11 HIGH and re-attaches interrupt (same as AVR)	
	
	switchInterruptAktiv = SWITCH_PRESS_READY;

	interrupts();
    // Interrupts werden nach ISR aktiviert
#endif
}
