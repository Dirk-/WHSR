
#include "WHSR.h"

// For copy & paste
#if defined(ARDUINO_AVR_NANO)
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

#define SWITCH_ADC_PULLUP 11  // D11, Pin 14, BINT
#define SWITCH_PIN A2               // A2 = D16 = ADC[2], BUT

// switchInterruptAktiv == 0: Kein Tastendruck erkannt
// switchInterruptAktiv == 2: Tastendruck im Interrupt erkannt, muss noch abgearbeitet werden
// switchInterruptAktiv == 3: Tastendruck im Interrupt erkannt, ist abgearbeitet
volatile unsigned char switchInterruptAktiv = 0;

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
	if(switchInterruptAktiv == 2)
	{
		switchInterruptAktiv = 3;
		return switchValue;
	}
	else
	{
#if defined(ARDUINO_AVR_NANO)
    DoCheckADCMode(SWITCH_ADC);
	int adcValue = mySensorValues[SWITCH_ADC];
	adcValue = adcValue == 0 ? 1 : adcValue; // Don't divide by zero
    return (unsigned char)(((10160000L / adcValue - 10000L) * SwitchFactor + 5000L) / 10000);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
	int adcValue = analogRead(SWITCH_ADC);
    DebugSerial_print("SWITCH_ADC: ");
    DebugSerial_println(adcValue);
	adcValue = adcValue == 0 ? 1 : adcValue; // Don't divide by zero
    return (unsigned char)(((10160000L / adcValue - 10000L) * SwitchFactor + 5000L) / 10000);
#endif
    }
}

//
// Turn On the PinChange Interrupt
//
void WHSR::switchInterruptOn(void)
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
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), SwitchISR, CHANGE);
#endif

    SWITCH_INTERRUPT_STATE = SWITCH_INTERRUPT_IDLE;
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

    SWITCH_INTERRUPT_STATE = SWITCH_INTERRUPT_NONE;
}

//
//	Return true if Switch was pressed
//
bool WHSR::switchAvailable()
{
	return switchInterruptAktiv == 2 ? true : false;
}

//
// Pin Change Interrupt Service Routine
//
void WHSR::switchInterrupt(void)
{
    // Interrupts sind deaktiviert beim Eintritt in ISR

	// Interrupt verhindern wenn
	if(switchInterruptAktiv == 3 && digitalRead(SWITCH_PIN) == HIGH)
	{
		switchInterruptAktiv = 0;
		return; 
	}
	
	if(switchInterruptAktiv != 0 ||		// Wenn schon einmal ein Button gedrückt wurde oder
	   digitalRead(SWITCH_PIN) == HIGH)	// wenn kein Button gedrückt wurde
		return;
	
	++switchInterruptAktiv;
	noInterrupts();
	
    // Ausschalten, damit der analoge Wert gelesen werden kann
	switchInterruptOff();

	switchValue = 0;
	//unsigned long startMillis = millis(); //Aktuellen Zeitstempel speichern
	//while (switchValue == 0 && (millis() - startMillis < 1000)) 
		switchValue = readSwitches();

    // Wieder einschalten
	switchInterruptOn();	
	
	++switchInterruptAktiv;

	interrupts();
    // Interrupts werden nach ISR aktiviert
}
