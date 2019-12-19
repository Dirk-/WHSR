
#include "WHSR.h"

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
	
	//ADCSRA |= (1<<ADSC);				// Start ADC
	
	DebugSerial_println(F(" - Finished"));
}

//
// ADC Start Next
//		Sobald ein Channel gelesen wurde wird der nächste gestartet
//
void WHSR::ADCStartNext(void)
{
	++ADCPos;
	if((SwitchStateInterrupt & 0b1) == 0 && ADCPos == Switch)
		++ADCPos;

	if(ADCPos >= MaxADCChannels)
	{
		ADCPos = 0;
		if(SwitchStateInterrupt == SwitchState_Wait)
			SwitchStateInterrupt = SwitchState_Do;
		
		ADCBlockPassed = true;		
		
		if(ADCMode == ADCMode_Block)
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
	ADCPos = Channel; // % MaxADCChannels;
	SetADMUX(ADCPos);
	
	delayMicroseconds(100);
	ADCSRA |= (1<<ADSC); // Start ADC
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
	while (bit_is_set(ADCSRA, ADSC));
}

//
// ADC Interrupt Routine
//		Für Einzellesungen warten bis ADC beendet ist
//
void WHSR::ADCInterrupt(void)
{	
	mySensorValues[ADCPos] = ADC;
	/*
	DebugSerial_print(ADCPos, DEC);
	DebugSerial_print(F(" "));
	DebugSerial_println(mySensorValues[ADCPos]);
	*/
	if(ADCPos == Switch)
		SwitchStateInterrupt = SwitchState_Idle;
	
	if(ADCMode == ADCMode_Block)
		ADCStartNext();
}

//
//
//
void WHSR::SetADMUX(char pin)
{	
	if(pin == 8) pin = 14;

	ADMUX &= 0xf0;
	ADMUX |= (pin & 0b1111);
}

//
//
//

void WHSR::DoCheckADCMode(char channel)
{
	if(ADCMode == ADCMode_None)
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






