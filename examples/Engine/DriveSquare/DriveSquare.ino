
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Engine drive Square");
}

void loop()
{
	int timeForTurning = 200;	// Estimated time for making a right turn in full speed
	int timeForOneEdge = 200;
	int speed = 200;
	
	for (int i=0; i<4; i++)
	{	
    	// Drive forward
    	robo.setMotorSpeed(speed, speed);
    	robo.setMotorDirection (FWD, FWD);
    	delay (timeForOneEdge);

    	// Turn right
    	robo.setMotorSpeed(MAX_SPEED, MAX_SPEED);
    	robo.setMotorDirection (FWD, RWD);
    	delay (timeForTurning);
	}
    robo.setMotorSpeed(0, 0);
}