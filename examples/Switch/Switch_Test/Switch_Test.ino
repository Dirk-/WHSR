
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	
	Serial.println("Switch Test");
}

void loop()
{
  int switchvalue = robo.readSwitches();

  Serial.print(switchvalue, BIN);
  Serial.print(" (");
  Serial.print(switchvalue);
  Serial.println(")");
  
  delay(100);
}
