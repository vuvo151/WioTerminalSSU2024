#include "Seeed_BME280.h"
#include <Wire.h>
BME280 bme280;
void setup() {
  Serial.begin(9600);
  if (!bme280.init()) {
    Serial.println("Device error!");
  }
}
void loop() {
  float pressure;
  //get temperatures
  Serial.print("Temp: ");
  Serial.print(bme280.getTemperature());
  Serial.println("C");

  //get atmospheric pressure data
  Serial.print("Pressure: ");
  Serial.print(pressure = bme280.getPressure());
  Serial.println("Pa");

  //get altitude data
  Serial.print("Altitude: ");
  Serial.print(bme280.calcAltitude(pressure));
  Serial.println("m");

  //get humidity data
  Serial.print("Humidity: ");
  Serial.print(bme280.getHumidity());
  Serial.println("%");
  delay(1000);
}


