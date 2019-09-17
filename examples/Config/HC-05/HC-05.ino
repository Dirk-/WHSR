
#define BaudRate 9600
#define NewName "HM10_01"

void setup()
{
  Serial.begin(Baudrate);
  Serial.println("Config HC-05");
  Serial.println("Remember that both devices, the Arduino and the HC-05 need to use the same baud rate.");
  Serial.println();
  Serial.println();

  Serial.println("AT+NAME=" + NewName);
  Serial.println("AT+UART=115200,1,0"); // New baud rate: 115200, 1 stop bit, 0 parity enter
}

void loop()
{
}
