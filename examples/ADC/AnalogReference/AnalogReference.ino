
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Analog Reference Test");
}

void loop()
{
	Serial.println(robo.readVreference());
	delay(100);
}
