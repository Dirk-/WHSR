
#include <WHSR.h>

WHSR robo = WHSR();

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