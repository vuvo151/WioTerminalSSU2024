#include "Seeed_BME280.h"
#include <Wire.h>
#include "TFT_eSPI.h" 
#include "imgArray.h"
#include "rpcWiFi.h" //Wi-Fi library 
#include "ThingSpeak.h"

const char* ssid = "_enter_ssid_of_wifi";
const char* password =  "_enter_wifi_password";

const char* serverName = "api.thingspeak.com";
const char * apiKey = "enter_your_api_key";

unsigned long ChannelNumber = <channel_in_numer>;

WiFiClient client;

TFT_eSPI tft; //initialize TFT LCD 
BME280 bme280;
int imgW = 60; int imgH = 60;
int row = 0; int col = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (!bme280.init()) {
    Serial.println("BME error!");
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

  ThingSpeak.begin(client);

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

  int temperature = (int)(bme280.getTemperature());
  int humidity = (int)(bme280.getHumidity());
  int pressure = (int)(bme280.getPressure());

  tft.fillRect(100,60, 150, 60, TFT_WHITE);
  tft.fillRect(100,120, 150, 60, TFT_WHITE);
  tft.fillRect(100,180, 150, 60, TFT_WHITE);

  tft.setFreeFont(&FreeSans12pt7b);
  tft.drawString((String)(temperature), 120, 70);
  tft.drawString((String)(humidity), 120, 130);
  tft.drawString((String)(pressure), 120, 190);

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, pressure);

  int x = ThingSpeak.writeFields(ChannelNumber, apiKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(15000);
}