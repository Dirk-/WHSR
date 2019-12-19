
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	robo.switchInterruptOn();
	Serial.println("Switch Interrupt Test");
}

void loop()
{
	if(robo.switchAvailable())
	{
		Serial.println(robo.readSwitches(), BIN);
	}

	// Simulate busy behaviour (but interrupt will be registered)
	delay(2000);
}