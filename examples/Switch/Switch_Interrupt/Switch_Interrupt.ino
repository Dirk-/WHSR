
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	robo.switchInterruptOn();
	Serial.println(F("Switch Interrupt Test"));
}

void loop()
{
	if(robo.switchAvailable())
	{
		Serial.println(robo.readSwitches(), BIN);
	}
}