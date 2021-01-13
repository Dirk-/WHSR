/*
  Switch_Interrupt

  This example for the Westphalian University's WHSR lerning robot  
  is used to check which switch has been pressed. It does not work properly
  on the Arduino Nano 33 BLE. 

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
	robo.switchInterruptOn();					// Turn On the PinChange Interrupt
	Serial.println("Switch Interrupt Test");
}

void loop()
{
	// Simulate busy behaviour (but interrupt will be registered)
	delay(2000);

	if (robo.switchAvailable())
	{	
		Serial.print("Switches pressed: ");
		// Print switch input value in binary form, should show a 1 for each pressed switch 
		// This is not compatible with the Arduino Nano 33 BLE.
		Serial.println(robo.readSwitches(), BIN);
	} else
	{
		Serial.println("Nothing detected.");
	}
}