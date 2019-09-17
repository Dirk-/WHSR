
#include <WHSR.h>

WHSR robo = WHSR();
int speed;
int directionSwitch;

void setup()
{
	robo.Init();
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
		speed = 100;
		directionSwitch = directionSwitch * (-1);
		robo.setMotorDirection(FWD * directionSwitch, RWD * directionSwitch);
	}
	
}