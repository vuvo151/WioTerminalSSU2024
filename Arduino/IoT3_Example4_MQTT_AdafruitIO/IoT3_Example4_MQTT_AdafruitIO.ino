#include "Seeed_BME280.h"
#include <Wire.h>
#include "TFT_eSPI.h" 
#include "rpcWiFi.h"
#include "imgArray.h"

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

TFT_eSPI tft; //initialize TFT LCD 
BME280 bme280;

int imgW = 60; int imgH = 60;
int row = 0; int col = 0;

const char* ssid = "_enter_ssid_of_wifi";
const char* password =  "_enter_wifi_password"; 
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "enter_your_aio_api_key"
#define AIO_KEY         "your_aio_key"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pressure");


void MQTT_connect();

void setup() {
  Serial.begin(115200);
  while(!Serial);

  while (!bme280.init()) {
    Serial.println("Device error - BME280!");
    delay(200);
  }

  WiFi.mode(WIFI_STA); //set WiFi to station mode 
  WiFi.disconnect(); 

  Serial.println("Connecting to WiFi.."); //print string 
  WiFi.begin(ssid, password); //connect to Wi-Fi network
  // WiFi.begin(ssid, NULL);

  // attempt to connect to Wi-Fi network:
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(250);
  }
  Serial.print("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); //print Wio Terminal's IP address

  tft.begin(); //start TFT LCD 
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE); 
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setTextColor(TFT_BLACK); 
  tft.drawString("Weather Dashboard",40,20);  

 for (row = 0; row < imgH; row++) {
  for (col = 0; col < imgW; col++) {
    int pixelIndex = (row * imgW + col) * 2;
    uint16_t pixelValue = (baroTemperature[pixelIndex] << 8) | baroTemperature[pixelIndex + 1];
    tft.drawPixel(40 + col, 60 + row, pixelValue);
  }
 }

  for (row = 0; row < imgH; row++) {
    for (col = 0; col < imgW; col++) {
      int pixelIndex = (row * imgW + col) * 2;
      uint16_t pixelValue = (baroHumidity[pixelIndex] << 8) | baroHumidity[pixelIndex + 1];
      tft.drawPixel(40 + col, 120 + row, pixelValue);
    }
  }

  for (row = 0; row < imgH; row++) {
    for (col = 0; col < imgW; col++) {
      int pixelIndex = (row * imgW + col) * 2;
      uint16_t pixelValue = (baroAtmosphere[pixelIndex] << 8) | baroAtmosphere[pixelIndex + 1];
      tft.drawPixel(40 + col, 180 + row, pixelValue);
    }
 }

  for (row = 0; row < 65; row++) {
    for (col = 0; col < 65; col++) {
      int pixelIndex = (row * 65 + col) * 2;
      uint16_t pixelValue = (ssuLogo3[pixelIndex] << 8) | ssuLogo3[pixelIndex + 1];
      tft.drawPixel(255 + col, 175 + row, pixelValue);
    }
 }

}

void loop() {

  uint32_t temp = (uint32_t)(bme280.getTemperature());
  uint32_t humid = (uint32_t)(bme280.getHumidity());
  uint32_t press = (uint32_t)(bme280.getPressure());

  // Serial.print("Connecting to ");
  // Serial.println(serverName);

  MQTT_connect();

  if (! temperature.publish(temp)) {
    Serial.println(F("temperature: Failed"));
  } else {
    Serial.println(F("temperature: OK!"));
  }

  delay(2000);

    if (! humidity.publish(humid)) {
    Serial.println(F("humidity: Failed"));
  } else {
    Serial.println(F("humidity: OK!"));
  }
  delay(2000);

    if (! pressure.publish(press)) {
    Serial.println(F("pressure: Failed"));
  } else {
    Serial.println(F("pressure: OK!"));
  }
                             
    Serial.println("Sent to Adafruit.");

    tft.fillRect(100,60, 150, 60, TFT_WHITE);
    tft.fillRect(100,120, 150, 60, TFT_WHITE);
    tft.fillRect(100,180, 150, 60, TFT_WHITE);
    tft.setFreeFont(&FreeSans12pt7b);
    tft.drawString((String)(temp), 120, 70);
    tft.drawString((String)(humid), 120, 130);
    tft.drawString((String)(press), 120, 190);

  Serial.println("Waiting...");
  delay(2000);
}

void MQTT_connect()
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT… ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds…");
    mqtt.disconnect();

    delay(2000); // wait 5 seconds

    retries--;
    if (retries == 0) {
      while (1);
    }
  }

  Serial.println("MQTT Connected!");
}
  