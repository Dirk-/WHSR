
#include "WHSR.h"

//
//	Diese Funktion initialisiert die RGB-LED
//
void WHSR::initLEDs(void)
{
    DebugSerial_print(F("Init LEDS"));
	
	pinMode(STATUSLED_BLUE_DPIN, OUTPUT);
	digitalWrite(STATUSLED_BLUE_DPIN, LOW);
	
	pinMode(STATUSLED_GREEN_DPIN, OUTPUT);
	digitalWrite(STATUSLED_GREEN_DPIN, LOW);
	
	pinMode(STATUSLED_RED_DPIN, OUTPUT);
	digitalWrite(STATUSLED_RED_DPIN, LOW);
	
    DebugSerial_println(" - Finished"); 
}

//
//	MitHilfe dieser Funkion kan die Status-LED auf eine Farbe gesetzt werden
//
void WHSR::setStatusLED(unsigned char color)
{
	DebugSerial_print(F("Color: "));
	DebugSerial_println(color, BIN);
	
	digitalWrite(STATUSLED_RED_DPIN, (color & COLOR_RED) > 0 ?
							HIGH :
							LOW);
	
	digitalWrite(STATUSLED_GREEN_DPIN, (color & COLOR_GREEN) > 0 ?
							HIGH :
							LOW);
	
	digitalWrite(STATUSLED_BLUE_DPIN, (color & COLOR_BLUE) > 0 ?
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
		digitalWrite(LINE_FOLLOWER_LED_DPIN, HIGH);
	else
		digitalWrite(LINE_FOLLOWER_LED_DPIN, LOW);

}

//
//	Diese Funktion schaltet die ACS-LEDs (LED fuer die Fruehwarnung) ein oder aus
//
void WHSR::setIrLEDs(unsigned char status)
{
	if(status == LED_ON)
		digitalWrite(ACS_IR_LED_DPIN, HIGH);
	else
		digitalWrite(ACS_IR_LED_DPIN, LOW);
}