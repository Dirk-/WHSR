
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	Serial.println(F("ACS Test"));
}

void loop()
{
	int data[2];
	
	// Get Sensor Werte, Light On
	robo.readDistance(data, LEDOn);
	Serial.print(F("ACS; Light On: "));
	Serial.print(F("Left: "));
	Serial.println(data[Sensor_Left]);
	Serial.print(F("Right: "));
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	// Get Sensor Werte, Light Off
	//robo.readDistance(data, LEDOff); // Je nachdem ob die IRLeds an
	robo.readDistance(data);			 // ist oder nicht
	Serial.print(F("ACS; Light Off "));
	Serial.print(F("Left: "));
	Serial.println(data[Sensor_Left]);
	Serial.print(F("Right: "));
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	/*
	// Get Sensor Werte, Light On
	Serial.print(F("ACS; Light On: "));
	Serial.print(F("Left: "));
	Serial.println(robo.readDistance(Sensor_Left, LEDOn));
	Serial.print(F("Right: "));
	Serial.println(robo.readDistance(Sensor_Right, LEDOn));
	delay(1000);
	
	// Get Sensor Werte, Light Off
	Serial.print(F("ACS; Light Off: "));
	Serial.print(F("Left: "));
	//Serial.println(robo.readDistance(Sensor_Left, LEDOff)); // Siehe oben
	Serial.println(robo.readDistance(Sensor_Left));
	Serial.print(F("Right: "));
	//Serial.println(robo.readDistance(Sensor_Right, LEDOff)); // Siehe oben
	Serial.println(robo.readDistance(Sensor_Right));
	delay(1000);*/
	
	
}
