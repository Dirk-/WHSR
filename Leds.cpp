
#include "WHSR.h"

//
//	Diese Funktion initialisiert die RGB LED
//
void WHSR::InitLEDs(void)
{
    DebugSerial_print(F("Init LEDS"));
	
	pinMode(LED_Blue, OUTPUT);
	digitalWrite(LED_Blue, LED_Status_Pegel_Off);
	
	pinMode(LED_Green, OUTPUT);
	digitalWrite(LED_Green, LED_Status_Pegel_Off);
	
	pinMode(LED_Red, OUTPUT);
	digitalWrite(LED_Red, LED_Status_Pegel_Off);
	
    DebugSerial_println(" - Finished"); 
}

//
//	MitHilfe dieser Funkion kan die Status LED auf eine Farbe gesetzt werden
//
void WHSR::setStatusLED(unsigned char color)
{
	DebugSerial_print(F("Color: "));
	DebugSerial_println(color, BIN);
	
	digitalWrite(LED_Red, (color & Color_Red) > 0 ?
							LED_Status_Pegel_On :
							LED_Status_Pegel_Off);
	
	digitalWrite(LED_Green, (color & Color_Green) > 0 ?
							LED_Status_Pegel_On :
							LED_Status_Pegel_Off);
	
	digitalWrite(LED_Blue, (color & Color_Blue) > 0 ?
							LED_Status_Pegel_On :
							LED_Status_Pegel_Off);
		
	
	// Pin Map LED D5 - D7... PD5 - PD7
	//Write Port Alternative Moeglichkeit - schnellere Operation
	//PORTD = PORTD | color << 5; // B10101000;
}

//
//	Diese Funktion setzt die Status LED auf die verschiedenen Farben
//	Feste reinfolge
//
void WHSR::shiftStatusLED(void)
{
	static unsigned char pos = 0;
	setStatusLED(pos++);
}

//
//	Diese Funktion Schaltet die Front LED (LED fuer den Linienfolger) ein oder aus
//
void WHSR::setFrontLED(unsigned char status)
{
	if(status == LEDOn)
		digitalWrite(LineFollower_LED, LED_Sensor_Pegel_On);
	else
		digitalWrite(LineFollower_LED, LED_Sensor_Pegel_Off);

}

//
//	Diese Funktion Schaltet die ACS LEDs (LED fuer die Fruehwarnung) ein oder aus
//
void WHSR::setIrLEDs(unsigned char status)
{
	if(status == LEDOn)
		digitalWrite(ACS_IrLED, LED_Sensor_Pegel_On);
	else
		digitalWrite(ACS_IrLED, LED_Sensor_Pegel_Off);
}