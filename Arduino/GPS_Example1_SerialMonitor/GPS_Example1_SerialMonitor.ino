#include <SoftwareSerial.h>
SoftwareSerial gps(0, 1);
void setup() 
{
  Serial.begin(115200);
  gps.begin(9600);
}
void loop() 
{
if (gps.available())
  Serial.write(gps.read());
}

