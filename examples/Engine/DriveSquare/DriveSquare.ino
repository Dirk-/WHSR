
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

	Serial.println("Engine drive square");
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