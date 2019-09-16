
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println(F("StatusLED Test"));
}

void loop()
{
/*
	robo.setStatusLED(Color_Red);
	delay(10000);
	robo.setStatusLED(Color_Green);
	delay(10000);
	robo.setStatusLED(Color_Blue);
	delay(10000);
	robo.setStatusLED(Color_Yellow);
	delay(10000);
	robo.setStatusLED(Color_Magenta);
	delay(10000);
	robo.setStatusLED(Color_Cyan);
	delay(10000);
	robo.setStatusLED(Color_White);
	delay(10000);
	robo.setStatusLED(Color_Black);
	delay(10000); 
*/
	robo.shiftStatusLED();
	delay(500);
}