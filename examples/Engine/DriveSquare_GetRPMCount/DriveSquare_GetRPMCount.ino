
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();

	// Wait some time to give the user opportunity to program the robot before it starts moving
	robo.setStatusLED(Color_Red);
	delay(1000);
	robo.setStatusLED(Color_Yellow);
	delay(1000);
	robo.setStatusLED(Color_Green);
	delay(1000);

	Serial.println("Engine drive Square; Get RPM Count");
}

void loop()
{
	int data[2];
	int timeForTurning = 200;	// Estimated time for making a right turn in full speed
	int timeForOneEdge = 3000;	// Drive straight on for three seconds
	int speed = 200;
	
	for (int i=0; i<4; i++)	// Drive a square
	{	
    	// Drive forward
    	setMotorSpeed(speed, speed);
    	setMotorDirection (FWD, FWD);
    	delay (timeForOneEdge);

		robo.GetRPMSensorCount(data);
		Serial.print("Left: ");
		Serial.print(data[Sensor_Left]);
		Serial.print("; Right: ");
		Serial.println(data[Sensor_Right]);
		
    	// Turn right
    	setMotorSpeed(MAX_SPEED, MAX_SPEED);
    	setMotorDirection (FWD, RWD);
    	delay (timeForTurning);
		
		robo.GetRPMSensorCount(data);
		Serial.print("Left: ");
		Serial.print(data[Sensor_Left]);
		Serial.print("; Right: ");
		Serial.println(data[Sensor_Right]);
		
		Serial.println();
	}

	// Pause for two seconds
    setMotorSpeed(0, 0);
	delay (2000);
}