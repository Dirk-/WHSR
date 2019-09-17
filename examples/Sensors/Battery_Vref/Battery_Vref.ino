
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Battery & Vref Test");
}

void loop()
{
	Serial.print("Vref: ");
	Serial.println(robo.readVref());
	
	Serial.print("Vbat: ");
	Serial.println(robo.readBattery());
	delay(1000);
}
