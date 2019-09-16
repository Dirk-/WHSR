
#include <Robot.h>
Robot robo = Robot();

unsigned long sum = 0;
unsigned long counter = 0;
unsigned long previousMillis = 0;

void setup()
{
	robo.ADCMode = ADCMode_Block;
	robo.Init();
		
	Serial.println(F("Block Mode Test"));
}

void loop()
{
	unsigned long currentMillis = millis();
	if(currentMillis - previousMillis > 1000)
	{
		previousMillis = currentMillis;
		
		float avg = sum / counter;
		
		Serial.println(robo.readReferenz());
		
		Serial.print(F("AVG: "));
		Serial.println((int)avg);
    
		Serial.print(F(" sum: "));
		Serial.println(sum);
		
		Serial.print(F(" Counter: "));
		Serial.println(counter);
				
		sum = 0;
		counter = 0;
	}
  
	if(robo.ADCWaitForBlock())
	{
		sum += robo.readReferenz();
		++counter;
	}
}
