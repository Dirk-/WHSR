/*
  StatusLED

  This example for the Westphalian University's WHSR lerning robot  
  serves as a test program to check the functionalities of the LED. 

  This example code is in the public domain. For more information, see
  https://github.com/Dirk-/WHSR
*/

#include <WHSR.h>

// We need one instance of the WHSR class to handle the robot
WHSR robo = WHSR();

void setup()
{
	// Initialize all functional modules of the robot
	robo.Init();
	Serial.println("StatusLED Test");
}

void loop()
{
	robo.setStatusLED(COLOR_RED);			// The constant is used to set a color
	delay(2000);							// Pause between color change
	robo.setStatusLED(COLOR_GREEN);
	delay(2000);							// Pause for two seconds
	robo.setStatusLED(COLOR_BLUE);
	delay(2000);
	robo.setStatusLED(COLOR_YELLOW);
	delay(2000);
	robo.setStatusLED(COLOR_MAGENTA);
	delay(2000);
	robo.setStatusLED(COLOR_CYAN);
	delay(2000);
	robo.setStatusLED(COLOR_WHITE);
	delay(2000);
	robo.setStatusLED(COLOR_BLACK);
	delay(2000); 
}