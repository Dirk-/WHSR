
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Distance Test");
}

void loop()
{
	// Array for sensor results (left, right)
	int data[2];
	
	// Read distance sensors, IR LEDs on
	robo.readDistance(data, LEDOn);

	Serial.print("ACS; Light On: ");
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	// Read distance sensors, IR LEDs off
	robo.readDistance(data, LEDOff); 

	Serial.print("ACS; Light Off ");
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	delay(1000);
}
