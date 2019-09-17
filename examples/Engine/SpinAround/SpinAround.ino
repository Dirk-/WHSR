
#include <WHSR.h>

WHSR robo = WHSR();
int speed;

void setup()
{
	robo.Init();
	speed = 100;
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
	} 
}