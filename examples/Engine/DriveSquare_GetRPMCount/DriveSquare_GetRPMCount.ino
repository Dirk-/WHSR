
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();

	// Wait some time to give the user a chance to program the robot before it starts moving
	robo.setStatusLED(Color_Red);
	delay(1000);
	robo.setStatusLED(Color_Yellow);
	delay(1000);
	robo.setStatusLED(Color_Green);
	delay(1000);
  	robo.setStatusLED(Color_Off);

	Serial.println("Engine drive Square; Get RPM Count");
}

void loop()
{
	int data[2];
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
		robo.GetRPMSensorCount(data);
		Serial.print("Left: ");
		Serial.print(data[Sensor_Left]);
		Serial.print("; Right: ");
		Serial.println(data[Sensor_Right]);
		
      	robo.setMotorSpeed(0, 0);

    	// Turn right
    	robo.setMotorDirection (FWD, RWD);
    	robo.setMotorSpeed(speed, speed);
    	delay (timeForTurning);
		
		// Get rotational sensor values
		robo.GetRPMSensorCount(data);
		Serial.print("Left: ");
		Serial.print(data[Sensor_Left]);
		Serial.print("; Right: ");
		Serial.println(data[Sensor_Right]);
		
		Serial.println();
	}

	// Pause for two seconds
    robo.setMotorSpeed(0, 0);
	delay (2000);
}