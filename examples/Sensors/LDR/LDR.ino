
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("LDR Test");
}

void loop()
{
	int data[2];
	
	// Get Sensor Werte
	robo.readLDR(data);
	Serial.print("LDR"));
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	
	// Get Sensor Werte
	Serial.print("LDR");
	Serial.print("Left: ");
	Serial.println(robo.readLDR(Sensor_Left));
	Serial.print("Right: ");
	Serial.println(robo.readLDR(Sensor_Right));
		
	
	delay(1000);
}
