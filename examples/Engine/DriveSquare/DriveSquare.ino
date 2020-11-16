
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();

	// Wait some time to give the user a chance to program the robot before it starts moving
	robo.setStatusLED(COLOR_RED);
	delay(1000);
	robo.setStatusLED(COLOR_YELLOW);
	delay(1000);
	robo.setStatusLED(COLOR_GREEN);
	delay(1000);
  	robo.setStatusLED(COLOR_OFF);

	Serial.println("Engine drive square");
}

void loop() 
{
	int timeForTurning = 800;	// Estimated time for making a right turn
	int timeForOneEdge = 3000;	// Drive straight on for three seconds
	int speed = 120;
	
	for (int i=0; i<4; i++)		// Drive a square
	{	
    	// Drive forward
      	robo.setMotorDirection (FWD, FWD);
    	robo.setMotorSpeed(speed, speed);
    	delay (timeForOneEdge);

      	robo.setMotorSpeed(0, 0);

    	// Turn right
      	robo.setMotorDirection (FWD, RWD);
    	robo.setMotorSpeed(speed, speed);
    	delay (timeForTurning);
	}

	// Pause for two seconds
    robo.setMotorSpeed(0, 0);
	delay (2000);
}