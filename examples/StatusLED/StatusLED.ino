
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("StatusLED Test");
}

void loop()
{
/*
	robo.setStatusLED(COLOR_RED);
	delay(10000);
	robo.setStatusLED(COLOR_GREEN);
	delay(10000);
	robo.setStatusLED(COLOR_BLUE);
	delay(10000);
	robo.setStatusLED(COLOR_YELLOW);
	delay(10000);
	robo.setStatusLED(COLOR_MAGENTA);
	delay(10000);
	robo.setStatusLED(COLOR_CYAN);
	delay(10000);
	robo.setStatusLED(COLOR_WHITE);
	delay(10000);
	robo.setStatusLED(COLOR_BLACK);
	delay(10000); 
*/
	robo.shiftStatusLED();
	delay(500);
}