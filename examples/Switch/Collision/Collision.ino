/*
  Switch_Interrupt

  This example for the Westphalian University's WHSR lerning robot  
  is used to check for a collision (switch pressed). 

  This example code is in the public domain. For more information, see
  https://github.com/Dirk-/WHSR
*/

#include <WHSR.h>

// We need one instance of the WHSR class to handle the robot
WHSR robo = WHSR();

// This variable gets changed in the switch ISR, so you have to signal the compiler that it is volatile, 
// otherwise the compiler might optimize it away and your timer will not work as expected.
volatile bool collision = false;

// This is your switch Interrupt Service Routine (ISR). It should be as short as possible, 
// so we just set a flag here and do the actual work in the main loop.
void switchISR()
{
	collision = true;
}

void setup()
{
	// Initialize all functional modules of the robot
	robo.Init();

	// Wait for the user to switch to the Serial Monitor
	delay(3000);

	// Trigger my own ISR when switch gets pressed
	robo.switchInterruptOn(switchISR, FALLING); 

	Serial.println("Collision Test");
}

void loop()
{
	// Simulate busy behaviour (but interrupt will be registered)
	robo.setStatusLED(COLOR_GREEN);
	delay(200);

	if (collision)
	{	
		Serial.println("");
		Serial.println("Bumm!");
		collision = false;
	  	robo.setStatusLED(COLOR_RED);
		delay(500);
	} else {
		Serial.print("+");
	}
}