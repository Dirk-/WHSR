
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
  robo.ResistorOben = 33000.0;
  robo.ResistorUnten = 10000.0;
	robo.Init();
  Serial.println("Check Battery & Vref");
}

void loop()
{
 Serial.print("Vref: ");
  Serial.println(robo.readReferenceVoltage());
  
  Serial.print("Vbat: ");
  Serial.println(robo.readBatteryVoltage());
  delay(1000);
	
}
