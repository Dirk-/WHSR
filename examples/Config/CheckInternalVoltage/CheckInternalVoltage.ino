
#define BaudRate 9600

void setup()
{
  Serial.begin(BaudRate);
  Serial.println(F("Cech Internal Voltage"));
  Serial.println();
  
  analogReference(INTERNAL);
  delay(10000);
  
  Serial.println(F("Jetzt kann gemessen werden"));
}

void loop() {

}
