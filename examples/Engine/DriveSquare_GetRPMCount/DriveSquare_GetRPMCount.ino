
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Engine drive Square; Get RPM Count");
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
    setMotorSpeed(0, 0);
}