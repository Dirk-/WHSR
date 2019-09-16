
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	Serial.println(F("Analog Referenz Test"));
}

void loop()
{
	Serial.println(robo.readReferenz());
	delay(100);
}
