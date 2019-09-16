
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	Serial.println(F("Engine drive Square; Get RPM Count"));
}

void loop()
{
	int data[2];
	int timeForTurning = 200;	// Estimated time for making a right turn in full speed
	int timeForOneEdge = 200;
	int speed = 200;
	
	robo.GetRPMSensorCount(data);
	for (int i=0; i<4; i++)
	{	
    	// Drive forward
    	setMotorSpeed(speed, speed);
    	setMotorDirection (FWD, FWD);
    	delay (timeForOneEdge);

		robo.GetRPMSensorCount(data);
		Serial.print(F("Left: "));
		Serial.print(data[Sensor_Left]);
		Serial.print(F("; Right: "));
		Serial.println(data[Sensor_Right]);
		
    	// Turn right
    	setMotorSpeed(MAX_SPEED, MAX_SPEED);
    	setMotorDirection (FWD, RWD);
    	delay (timeForTurning);
		
		robo.GetRPMSensorCount(data);
		Serial.print(F("Left: "));
		Serial.print(data[Sensor_Left]);
		Serial.print(F("; Right: "));
		Serial.println(data[Sensor_Right]);
		
		Serial.println();
	}
    setMotorSpeed(0, 0);
}