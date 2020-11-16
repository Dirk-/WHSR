
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println("Linefollower Test");
}

void loop()
{
	// Array for sensor results (left, right)
	int data[2];
	
	// Read line sensors, LEDs on
	robo.readLinesensor(data, LED_ON);
	Serial.print("Linefollower; Light On ");
	Serial.print("Left: ");
	Serial.println(data[SENSOR_LEFT]);
	Serial.print("Right: ");
	Serial.println(data[SENSOR_RIGHT]);
	delay(1000);
	
	// Read line sensors, LEDs off
	robo.readLinesensor(data, LED_OFF);
	Serial.print("Linefollower; Light Off ");
	Serial.print("Left: ");
	Serial.println(data[SENSOR_LEFT]);
	Serial.print("Right: ");
	Serial.println(data[SENSOR_RIGHT]);
	delay(1000);
}
