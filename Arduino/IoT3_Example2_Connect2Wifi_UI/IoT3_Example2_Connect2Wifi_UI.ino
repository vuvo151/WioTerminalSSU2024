#include "TFT_eSPI.h" 
#include "rpcWiFi.h"

#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

TFT_eSPI tft; 

void setup() {
  Serial.begin(115200);
  while(!Serial);

  tft.begin(); //start TFT LCD 
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE); 
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setTextColor(TFT_BLACK); 

  WiFiManager wifiManager;
  wifiManager.resetSettings();

  tft.drawString("Connect your phone to",40,80); 
  tft.drawString("Wio Terminal Wifi",60,120); 

  wifiManager.autoConnect("Wio Terminal Wifi");
  WiFi.begin();

  tft.fillScreen(TFT_WHITE); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    tft.drawString("Connecting..",100,120);  
    delay(1000);
  }

  Serial.print("WiFi connected!  localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  tft.fillScreen(TFT_WHITE);  
  tft.drawString("WIFI CONNECTED!",40,100);  

}
void loop() {
}