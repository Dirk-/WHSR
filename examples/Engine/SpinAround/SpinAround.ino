
#include <WHSR.h>

WHSR robo = WHSR();
int speed;
int directionSwitch;

void setup()
{
	robo.Init();

	// Wait some time to give the user opportunity to program the robot before it starts moving
	robo.setStatusLED(Color_Red);
	delay(500);
	robo.setStatusLED(Color_Yellow);
	delay(500);
	robo.setStatusLED(Color_Green);
	delay(500);

	speed = 100;
	directionSwitch = 1;
	robo.setMotorDirection(FWD, RWD);
	Serial.println("Spin around");
}

void loop()
{
	if (speed < MAX_SPEED)
	{
		robo.setMotorSpeed(speed, speed);
		delay(25);
		speed++;
	} else
	{
		robo.setMotorSpeed(0, 0);
		delay(250);
		speed = 100;
		directionSwitch = directionSwitch * (-1);
		robo.setMotorDirection(FWD * directionSwitch, RWD * directionSwitch);
	}
	
}