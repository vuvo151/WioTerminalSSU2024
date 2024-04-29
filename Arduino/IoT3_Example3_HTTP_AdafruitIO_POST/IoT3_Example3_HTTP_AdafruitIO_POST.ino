#include "Seeed_BME280.h"
#include <Wire.h>
#include "TFT_eSPI.h" 
#include "rpcWiFi.h"
#include "imgArray.h"

TFT_eSPI tft; //initialize TFT LCD 
BME280 bme280;

int imgW = 60; int imgH = 60;
int row = 0; int col = 0;

const char* ssid = "_enter_ssid_of_wifi";
const char* password =  "_enter_wifi_password"; 
const char* serverName = "io.adafruit.com";
String AIOKey = "your_aio_key";
WiFiClient client;

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

  String temperature = (String)(bme280.getTemperature());
  String humidity = (String)(bme280.getHumidity());
  String pressure = (String)(bme280.getPressure());

  Serial.print("Connecting to ");
  Serial.println(serverName);

  if (!client.connect(serverName, 80)) {
    Serial.println("Connection failed!");
  } else {
    Serial.println("Connected to server!");

    String postData = "{ \"feeds\": [ ";

    postData += "{ \"key\": \"temperature\", ";
    postData += "  \"value\": \"" + temperature + "\" }, ";

    postData += "{ \"key\": \"humidity\", ";
    postData += "  \"value\": \"" + humidity + "\" },";

    postData += "{ \"key\": \"pressure\", ";
    postData += "  \"value\": \"" + pressure + "\" }";
    postData += " ] }";


    client.println("POST https://io.adafruit.com/api/v2/VuVu1122/groups/weatherinfo/data HTTP/1.0");
    client.println("Host: io.adafruit.com");
    client.println("Content-Type: application/json");
    client.println("X-AIO-Key: your_aio_key");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);
                             
    Serial.println("Sent to Adafruit.");

    tft.fillRect(100,60, 150, 60, TFT_WHITE);
    tft.fillRect(100,120, 150, 60, TFT_WHITE);
    tft.fillRect(100,180, 150, 60, TFT_WHITE);
    tft.setFreeFont(&FreeSans12pt7b);
    tft.drawString(temperature, 120, 70);
    tft.drawString(humidity, 120, 130);
    tft.drawString(pressure, 120, 190);

  }
  
  client.stop();
  Serial.println("Waiting...");
  delay(3000);
}