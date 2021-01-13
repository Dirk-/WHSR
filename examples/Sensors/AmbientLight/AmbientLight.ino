/*
  AmbientLight

  This example for the Westphalian University's WHSR lerning robot shows how to
  read out the values of the ambient light sensors of the robot.

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

	Serial.println("Ambient Light Test");
}

void loop()
{
	// Array for sensor results (left, right)
	int data[2];
	
	// Read ambient light sensor
	robo.readAmbientLight(data);

	// Communicate results
	Serial.println("---------- Ambient Light ---------");
	Serial.print("Left: ");
	Serial.println(data[SENSOR_LEFT]);
	Serial.print("Right: ");
	Serial.println(data[SENSOR_RIGHT]);
		
	// Pause for a second	
	delay(1000);	
}
