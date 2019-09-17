
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Engine drive Circular");
}

void loop()
{
	int maxSpeed = 200;
	
	int var = 0;
	if (maxSpeed > 255)
		maxSpeed = 255;
	
	robo.setMotorDirection(FWD, RWD);
	while(var < maxSpeed)
	{
		robo.setMotorSpeed(var, var);
		delay(25);
		var++;
	}
}