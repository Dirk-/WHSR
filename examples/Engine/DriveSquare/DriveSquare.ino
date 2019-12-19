
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

	Serial.println("Engine drive square");
}

void loop()
{
	int timeForTurning = 200;	// Estimated time for making a right turn in full speed
	int timeForOneEdge = 3000;	// Drive straight on for three seconds
	int speed = 200;
	
	for (int i=0; i<4; i++)		// Drive a square
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

	// Pause for two seconds
    robo.setMotorSpeed(0, 0);
	delay (2000);
}