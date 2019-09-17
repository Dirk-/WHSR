
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	robo.switchInterruptOn();
	Serial.println("Switch Interrupt Test - On _ Off");
}

void loop()
{
	bool wait = false;
	if(robo.switchAvailable())
	{
		Serial.println(robo.readSwitches(), BIN);
		wait = true;
		
		robo.switchInterruptOff();
		Serial.println("Interrupt - Turn Off");
	}
	
	if(wait)
	{
		delay(60000);
		robo.switchInterruptOn();
		Serial.println("Interrupt - Turn On");
	}
}