
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
	robo.readACS(data, LEDOn);
	Serial.print(F("ACS; Light On: "));
	Serial.print(F("Left: "));
	Serial.println(data[Sensor_Left]);
	Serial.print(F("Right: "));
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	// Get Sensor Werte, Light Off
	//robo.readACS(data, LEDOff); // Je nachdem ob die IRLeds an
	robo.readACS(data);			 // ist oder nicht
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
	Serial.println(robo.readACS(Sensor_Left, LEDOn));
	Serial.print(F("Right: "));
	Serial.println(robo.readACS(Sensor_Right, LEDOn));
	delay(1000);
	
	// Get Sensor Werte, Light Off
	Serial.print(F("ACS; Light Off: "));
	Serial.print(F("Left: "));
	//Serial.println(robo.readACS(Sensor_Left, LEDOff)); // Siehe oben
	Serial.println(robo.readACS(Sensor_Left));
	Serial.print(F("Right: "));
	//Serial.println(robo.readACS(Sensor_Right, LEDOff)); // Siehe oben
	Serial.println(robo.readACS(Sensor_Right));
	delay(1000);*/
	
	
}
