
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	Serial.println(F("LDR Test"));
}

void loop()
{
	int data[2];
	
	// Get Sensor Werte
	robo.readLDR(data);
	Serial.print(F("LDR"));
	Serial.print(F("Left: "));
	Serial.println(data[Sensor_Left]);
	Serial.print(F("Right: "));
	Serial.println(data[Sensor_Right]);
	
	// Get Sensor Werte
	Serial.print(F("LDR"));
	Serial.print(F("Left: "));
	Serial.println(robo.readLDR(Sensor_Left));
	Serial.print(F("Right: "));
	Serial.println(robo.readLDR(Sensor_Right));
		
	
	delay(1000);
}
