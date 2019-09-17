
// Baud rate for configuration
#define INIT_BAUDRATE 9600

// New name for device (should be unique in your hood)
#define NewName "HC05_01"

void setup()
{
  Serial.begin(INIT_BAUDRATE);
  Serial.println("Config HC-05");
  Serial.println("Remember that both devices, the Arduino and the HC-05 need to use the same baud rate.");
  Serial.println();
  Serial.println();

  Serial.print("AT+NAME");
  Serial.println(NewName);
  Serial.println("AT+UART=115200,1,0"); // New baud rate: 115200, 1 stop bit, 0 parity enter
}

void loop()
{
}
