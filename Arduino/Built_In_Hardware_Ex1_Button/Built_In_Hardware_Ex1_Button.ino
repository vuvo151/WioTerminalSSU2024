#include "TFT_eSPI.h" 
TFT_eSPI tft; //initialize TFT LCD 

void setup() 
{
  Serial.begin(115200);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);

  tft.begin(); //start TFT LCD 
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE); 
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setTextColor(TFT_BLACK); 
  tft.drawString("Built-In Button - Status",25,40);  

  tft.drawCircle(75,190,25,TFT_BLACK);  // button 1
  tft.drawCircle(150,190,25,TFT_BLACK); // button 2
  tft.drawCircle(225,190,25,TFT_BLACK); // button 3
}

void loop() {
  if(digitalRead(BUTTON_1) == LOW)
  {
    tft.fillRect(20,115, 280, 30, TFT_WHITE);
    tft.drawString("Button 1 is pressed!",40, 120); 
    tft.fillCircle(225,190,22,TFT_YELLOW);  // button 1
    delay(1000);
  }
  else if(digitalRead(BUTTON_2) == LOW)
  {
    tft.fillRect(20,115, 280, 30, TFT_WHITE);
    tft.drawString("Button 2 is pressed!",40, 120); 
    tft.fillCircle(150,190,22,TFT_YELLOW); // button 2
    delay(1000);
  }  
  else if(digitalRead(BUTTON_3) == LOW)
  {
    tft.fillRect(20,115, 280, 30, TFT_WHITE);
    tft.drawString("Button 3 is pressed!",40, 120); 
    tft.fillCircle(75,190,22,TFT_YELLOW); // button 3
    delay(1000);
  }
  else   {
    tft.fillRect(20,115, 280, 30, TFT_WHITE);
    tft.fillCircle(225,190,22,TFT_WHITE);  // button 1
    tft.fillCircle(150,190,22,TFT_WHITE); // button 2
    tft.fillCircle(75,190,22,TFT_WHITE); // button 3
    delay(1000);
  }
}
