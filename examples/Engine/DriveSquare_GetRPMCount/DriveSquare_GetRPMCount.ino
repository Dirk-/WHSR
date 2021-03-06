/*
  DriveSquare_GetRPMCount

  This example for the Westphalian University's WHSR lerning robot shows how to
  read out the values of the rotational sensors of the robot and how to drive a square
  with the robot.

  This example code is in the public domain. For more information,see
  https://github.com/Dirk-/WHSR
*/

#include <WHSR.h>

// We need one instance of the WHSR class to handle the robot
WHSR robo = WHSR();

void setup()
{
	// Initialize all functional modules of the robot
	robo.Init();

	// Wait some time to give the user a chance to program the robot before it starts moving
	robo.setStatusLED(COLOR_RED);
	delay(1000);
	robo.setStatusLED(COLOR_YELLOW);
	delay(1000);
	robo.setStatusLED(COLOR_GREEN);
	delay(1000);
  	robo.setStatusLED(COLOR_OFF);

	Serial.println("Engine drive Square; Get RPM Count");
}

void loop()
{
	unsigned long data[2];		// Array for sensor values (left, right)
	int timeForTurning = 800;	// Estimated time for making a right turn
	int timeForOneEdge = 3000;	// Drive straight on for three seconds
	int speed = 120;
	
	for (int i=0; i<4; i++)	// Drive a square
	{	
    	// Drive forward
    	robo.setMotorDirection (FWD, FWD);
    	robo.setMotorSpeed(speed, speed);
    	delay (timeForOneEdge);

		// Get rotational sensor values
		robo.getRPMSensorCount(data);
		Serial.print("Left: ");
		Serial.print(data[SENSOR_LEFT]);
		Serial.print("; Right: ");
		Serial.println(data[SENSOR_RIGHT]);
		
      	robo.setMotorSpeed(0, 0);

    	// Turn right
    	robo.setMotorDirection (FWD, RWD);
    	robo.setMotorSpeed(speed, speed);
    	delay (timeForTurning);
		
		// Get rotational sensor values
		robo.getRPMSensorCount(data);
		Serial.print("Left: ");
		Serial.print(data[SENSOR_LEFT]);
		Serial.print("; Right: ");
		Serial.println(data[SENSOR_RIGHT]);
		
		Serial.println();
	}

	// Pause for two seconds
    robo.setMotorSpeed(0, 0);
	delay (2000);
}