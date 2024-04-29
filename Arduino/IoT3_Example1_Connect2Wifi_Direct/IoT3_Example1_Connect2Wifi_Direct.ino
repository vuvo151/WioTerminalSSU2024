#include "TFT_eSPI.h" 
#include "rpcWiFi.h"

const char* ssid = "_enter_ssid_of_wifi"; //SSUWIFI
const char* password =  "_enter_wifi_password";  //password

TFT_eSPI tft; //initialize TFT LCD 

void setup() {
  Serial.begin(115200);
  while(!Serial);

  tft.begin(); //start TFT LCD 
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE); 
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setTextColor(TFT_BLACK); 
  tft.drawString("Connecting to WiFi..",40,100);  

  WiFi.mode(WIFI_STA); //set WiFi to station mode 
  WiFi.disconnect(); 

  Serial.println("Connecting to WiFi.."); //print string 
  // WiFi.begin(ssid, password); //connect to Wi-Fi network
  WiFi.begin(ssid, NULL);

  // attempt to connect to Wi-Fi network:
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(250);
  }
  Serial.print("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); //print Wio Terminal's IP address

  tft.fillScreen(TFT_WHITE); 
  tft.drawString("WIFI CONNECTED!",40,100);  

}
void loop() {
}