/*
  AnalogReference

  This example for the Westphalian University's WHSR lerning robot shows how to
  read out the reference voltage, which is used for the analog input of the robot.

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

	Serial.println("Analog Reference Test");
}

void loop()
{
	Serial.print("V Reference: ");
	Serial.println(robo.readVreference()); 		// Read reference voltage

	delay(100);		 							// Pause for 100 milliseconds
}
