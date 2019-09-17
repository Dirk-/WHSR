
#define BaudRate 9600

void setup()
{
  Serial.begin(BaudRate);
  Serial.println("Cech Internal Voltage");
  Serial.println();
  
  analogReference(INTERNAL);
  delay(10000);
  
  Serial.println("Jetzt kann gemessen werden");
}

void loop() {

}
