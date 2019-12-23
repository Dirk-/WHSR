
#include "WHSR.h"

//
// Initialisiert die Kollisionserkennung
//
void WHSR::InitSwitches(void)
{
	DebugSerial_print(F("Init Switches"));
	
	pinMode(Switch_On_Interrupt, OUTPUT);
	digitalWrite(Switch_On_Interrupt, LOW);
	
	DebugSerial_println(F(" - Finished"));
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
		DoCheckADCMode(Switch);
		return (unsigned char)(( ( 10160000L / mySensorValues[Switch] - 10000L ) * SwitchFactor + 5000L ) / 10000);
	}
}

//
// Turn On the PinChange Interrupt
//
void WHSR::switchInterruptOn(void)
{
	digitalWrite(Switch_On_Interrupt, HIGH);
	//delay(1);
	//pinMode(Switch_On_Interrupt, INPUT);
	//Serial.println(F(","));
	delay(2);
	
	byte pin = SwitchISRPin;
	*digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
	
	SwitchStateInterrupt = SwitchState_Idle;
}

//
// Turn Off the PinChange Interrupt
//
void WHSR::switchInterruptOff(void)
{
	//pinMode(Switch_On_Interrupt, OUTPUT);
	digitalWrite(Switch_On_Interrupt, LOW);
	delay(2);
	
	byte pin = SwitchISRPin;
    PCICR  &= ~bit (digitalPinToPCICRbit(pin)); // disable interrupt for the group
	SwitchStateInterrupt = SwitchState_None;
}

//
//	Return true if Switch was pressed
//
bool WHSR::switchAvailable()
{
	return switchInterruptAktiv == 2 ? true : false;
}

//
// Pin Change Interrupt Vector
//
void WHSR::switchInterrupt(void)
{
	DebugSerial_print(F("."));
	// Interrupt verhindern wenn
	if(switchInterruptAktiv == 3 && digitalRead(SwitchISRPin) == HIGH)
	{
		switchInterruptAktiv = 0;
		return; 
	}
	
	if(switchInterruptAktiv != 0 ||					// schon einmal ein Button degrückt wurde
	   digitalRead(SwitchISRPin) == HIGH)	// Wenn kein Button gedrückt wurde
		return;
	
	++switchInterruptAktiv;
	noInterrupts();
	
	switchInterruptOff();

	switchValue = 0;
	//unsigned long startMillis = millis(); //Aktuellen Zeitstempel speichern
	//while (switchValue == 0 && (millis() - startMillis < 1000)) 
		switchValue = readSwitches();

	switchInterruptOn();	
	
	++switchInterruptAktiv;
	DebugSerial_println(F("Switch Pressed"));
	interrupts();
}
