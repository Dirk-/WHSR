
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Ambient Light Test");
}

void loop()
{
	// Array for sensor results (left, right)
	int data[2];
	
	// Read ambient light sensor
	robo.readAmbientLight(data);

	// Communicate results
	Serial.println("---------- Ambient Light ---------");
	Serial.print("Left: ");
	Serial.println(data[SENSOR_LEFT]);
	Serial.print("Right: ");
	Serial.println(data[SENSOR_RIGHT]);
		
	delay(1000);
}
