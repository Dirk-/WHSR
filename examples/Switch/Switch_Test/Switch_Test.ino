
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	
	Serial.println(F("Switch Test"));
}

void loop()
{
  Serial.println(robo.readSwitches(), BIN);
  delay(100);
}
