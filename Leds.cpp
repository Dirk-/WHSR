
#include "WHSR.h"

//
//	Diese Funktion initialisiert die RGB-LED
//
void WHSR::InitLEDs(void)
{
    DebugSerial_print(F("Init LEDS"));
	
	pinMode(LED_Blue, OUTPUT);
	digitalWrite(LED_Blue, LOW);
	
	pinMode(LED_Green, OUTPUT);
	digitalWrite(LED_Green, LOW);
	
	pinMode(LED_Red, OUTPUT);
	digitalWrite(LED_Red, LOW);
	
    DebugSerial_println(" - Finished"); 
}

//
//	MitHilfe dieser Funkion kan die Status-LED auf eine Farbe gesetzt werden
//
void WHSR::setStatusLED(unsigned char color)
{
	DebugSerial_print(F("Color: "));
	DebugSerial_println(color, BIN);
	
	digitalWrite(LED_Red, (color & COLOR_RED) > 0 ?
							HIGH :
							LOW);
	
	digitalWrite(LED_Green, (color & COLOR_GREEN) > 0 ?
							HIGH :
							LOW);
	
	digitalWrite(LED_Blue, (color & COLOR_BLUE) > 0 ?
							HIGH :
							LOW);
		
	
	// Pin Map LED D5 - D7... PD5 - PD7
	//Write Port Alternative Moeglichkeit - schnellere Operation
	//PORTD = PORTD | color << 5; // B10101000;
}

//
//	Diese Funktion setzt die Status-LED auf die verschiedenen Farben
//	Feste Reihenfolge
//
void WHSR::shiftStatusLED(void)
{
	static unsigned char pos = 0;
	setStatusLED(pos++);
}

//
//	Diese Funktion schaltet die Front-LED (LED fuer den Linienfolger) ein oder aus
//
void WHSR::setFrontLED(unsigned char status)
{
	if(status == LED_ON)
		digitalWrite(LINE_FOLLOWER_LED_PIN, HIGH);
	else
		digitalWrite(LINE_FOLLOWER_LED_PIN, LOW);

}

//
//	Diese Funktion schaltet die ACS-LEDs (LED fuer die Fruehwarnung) ein oder aus
//
void WHSR::setIrLEDs(unsigned char status)
{
	if(status == LED_ON)
		digitalWrite(ACS_IR_LED_PIN, HIGH);
	else
		digitalWrite(ACS_IR_LED_PIN, LOW);
}