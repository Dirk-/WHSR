
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	robo.switchInterruptOn();
	Serial.println(F("Switch Interrupt Test - On _ Off"));
}

void loop()
{
	bool wait = false;
	if(robo.switchAvailable())
	{
		Serial.println(robo.readSwitches(), BIN);
		wait = true;
		
		robo.switchInterruptOff();
		Serial.println(F("Interrupt - Turn Off"));
	}
	
	if(wait)
	{
		delay(60000);
		robo.switchInterruptOn();
		Serial.println(F("Interrupt - Turn On"));
	}
}