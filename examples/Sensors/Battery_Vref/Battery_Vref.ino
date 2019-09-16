
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	Serial.println(F("Battery & Vref Test"));
}

void loop()
{
	Serial.print(F("Vref: "));
	Serial.println(robo.readVref());
	
	Serial.print(F("Vbat: "));
	Serial.println(robo.readBattery());
	delay(1000);
}
