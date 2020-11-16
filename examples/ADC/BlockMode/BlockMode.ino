
#include <WHSR.h>

WHSR robo = WHSR();

unsigned long sum = 0;
unsigned long counter = 0;
unsigned long previousMillis = 0;

void setup()
{
	robo.ADCMode = ADC_MODE_BLOCK;
	robo.Init();
		
	Serial.println("Block Mode Test");
}

void loop()
{
	unsigned long currentMillis = millis();
	if(currentMillis - previousMillis > 1000)
	{
		previousMillis = currentMillis;
		
		float avg = sum / counter;
		
		Serial.println(robo.readVreference());
		
		Serial.print("AVG: ");
		Serial.println((int)avg);
    
		Serial.print(" sum: ");
		Serial.println(sum);
		
		Serial.print(" Counter: ");
		Serial.println(counter);
				
		sum = 0;
		counter = 0;
	}
  
	if(robo.ADCWaitForBlock())
	{
		sum += robo.readVreference();
		++counter;
	}
}
