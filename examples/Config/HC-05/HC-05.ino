
#define BaudRate 9600
#define NewName "HM10_01"

void setup()
{
  Serial.begin(Baudrate);
  Serial.println(F("Config HC-05"));
  Serial.println(F("Remember that both devices, the Arduino and the HC-05 need to use the same baud rate."));
  Serial.println();
  Serial.println();

  Serial.println(F("AT+NAME=") + NewName);
  Serial.println(F("AT+UART=115200,1,0")); // New baud rate: 115200, 1 stop bit, 0 parity enter
}

void loop()
{
}
