
#include "WHSR.h"

// Hier wird der ADC-Wert gespeichert, wenn wir die Arduino-Routinen für Nano 33 BLE nutzen
// (Aquivalent zum ADC-Register des Nano)
int ADCvalue = 0;

/* ************************************************************************************
 *
 *	Init + Interrupt
 *
 * ************************************************************************************ */
 
//
//	Init ADC
//
void WHSR::InitADC(void)
{
	DebugSerial_print(F("Init ADC"));

#if defined(ARDUINO_AVR_NANO)
    ADCPos = 0;
	ADMUX = (0<<REFS1) | (1<<REFS0) | 	// ReferenzSpannung 01 -> Extern
			(0<<ADLAR) |				// Bit Orientierung 10 Bit in 2 Byte -> Right
			(0<<MUX3)  | (0<<MUX2) |	// Bits zum Selektieren des Channels
			(0<<MUX1)  | (0<<MUX0);		// Channel 0
	
	ADCSRA = (1<<ADEN)  | 				// Enables ADC
			 (0<<ADSC)  | 				// Start ADC
			 (0<<ADATE) |				// Enable Edge Rise Interrupt
			 (0<<ADIF)  |				// Flag Conversion Finished
			 (1<<ADIE)  | 				// Enables Interrupt
			 (1<<ADPS2) | (1<<ADPS1) |	// Select Prescaler
			 (1<<ADPS0); 				// 111 -> 128
										// 50KHz < FCPU / Prescaler < 200Khz
	
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

    DebugSerial_println(F(" - Finished"));
}

//
// ADC Start Next
//		Sobald ein Channel gelesen wurde wird der nächste gestartet
//
void WHSR::ADCStartNext(void)
{
	++ADCPos;
	if((SWITCH_INTERRUPT_STATE & 0b1) == 0 
        && ADCPos == SWITCH_ADC)    // Switches überspringen
		++ADCPos;

	if(ADCPos >= MAX_ADC_CHANNELS)
	{
		ADCPos = 0;
		if(SWITCH_INTERRUPT_STATE == SWITCH_INTERRUPT_WAIT)
			SWITCH_INTERRUPT_STATE = SWITCH_INTERRUPT_DO;
		
		ADCBlockPassed = true;		
		
		if(ADCMode == ADC_MODE_BLOCK)
			return;
	}
	
	SetADMUX(ADCPos);
}

//
// ADC Start
//		Lese Channel X
//
void WHSR::ADCStart(char Channel)
{
	ADCPos = Channel; // % MAX_ADC_CHANNELS;
	SetADMUX(ADCPos);
	
#if defined(ARDUINO_AVR_NANO)
    delayMicroseconds(100);
    ADCSRA |= (1 << ADSC); // Start ADC
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    ADCvalue = analogRead(ADCPos);  // Direkt auslesen
#endif
}

//
// ADC Wait for Block
//		Warte bis der komplette Block gelesen wurde
//		Block => Alle 9 Kanäle
//
bool WHSR::ADCWaitForBlock(void)
{
	if(ADCBlockPassed)
	{
		ADCBlockPassed = false;
		return true;
	}
	
	return false;
}

//
// ADC Wait For Conversion
//		Für Einzellesungen warten bis ADC beendet ist
//
void WHSR::ADCWaitForConversion(void)
{
#if defined(ARDUINO_AVR_NANO)
    while (bit_is_set(ADCSRA, ADSC)) // ADC Status Register ADC Start Conversion ist 1 während Umwandlung
        ;
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    // Direkt zurückkommen
#endif
}

//
// ADC Interrupt Routine
//		Für Einzellesungen warten bis ADC beendet ist
//
void WHSR::ADCInterrupt(void)
{
    // Ergebnis der Wandlung im Sensor-Array speichern
#if defined(ARDUINO_AVR_NANO)
    mySensorValues[ADCPos] = ADC;
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    mySensorValues[ADCPos] = ADCvalue;
#endif

    /*
	DebugSerial_print(ADCPos, DEC);
	DebugSerial_print(F(" "));
	DebugSerial_println(mySensorValues[ADCPos]);
	*/
    if(ADCPos == SWITCH_ADC)
		SWITCH_INTERRUPT_STATE = SWITCH_INTERRUPT_IDLE;
	
	if(ADCMode == ADC_MODE_BLOCK)
		ADCStartNext();
}

//
// Setze den AD-Kanal
//
void WHSR::SetADMUX(char pin)
{
#if defined(ARDUINO_AVR_NANO)
    if (pin == 0b1000) // 8 -> 14 TODO: Wozu das??
        pin = 0b1110;

    ADMUX &= 0xf0;              // Kanal-Bits auf null setzen
	ADMUX |= (pin & 0b1111);    // Gewünschten Kanal wählen
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif
}

//
// ADC-Test mit Debug-Ausgabe
//
void WHSR::DoCheckADCMode(char channel)
{
	if(ADCMode == ADC_MODE_NONE)
	{
		ADCStart(channel);
		ADCWaitForConversion();
		
		DebugSerial_print(F(" "));
		DebugSerial_print(channel, DEC);
		DebugSerial_print(F(": "));
		DebugSerial_print(mySensorValues[channel]);
		DebugSerial_print(F(". "));
	}
}






