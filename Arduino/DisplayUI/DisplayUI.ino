#include "TFT_eSPI.h" //include TFT LCD library 
#include "imgArray.h"

TFT_eSPI tft; //initialize TFT LCD 
int imgWt = 60; int imgHt = 60;
int imgWh = 60; int imgHh = 60;
int row = 0; int col = 0;

void setup() {
  
  tft.begin(); //start TFT LCD 
  tft.setRotation(3); //set screen rotation 
  tft.fillScreen(TFT_WHITE); //fill background 

  tft.setFreeFont(&FreeSansBold12pt7b); //set font type 
  tft.setTextColor(TFT_BLACK); //set text color 
  tft.drawString("Simple UI",100,20); //draw text string 
  tft.drawString("Mechatronics 2024",50,50);

  for (row = 0; row < imgHt; row++) {
      for (col = 0; col < imgWt; col++) {
          int pixelIndex = (row * imgWt + col) * 2;
          uint16_t pixelValue = (tempLogo[pixelIndex] << 8) | tempLogo[pixelIndex + 1];
          tft.drawPixel(40 + col, 80 + row, pixelValue);
      }
  }

  for (row = 0; row < imgHh; row++) {
    for (col = 0; col < imgWh; col++) {
        int pixelIndex = (row * imgWh + col) * 2;
        uint16_t pixelValue = (humidLogo[pixelIndex] << 8) | humidLogo[pixelIndex + 1];
        tft.drawPixel(40 + col, 160 + row, pixelValue);
    }
  }
  tft.drawRect(100,100,160,30,TFT_NAVY);
  tft.fillRect(100,100,90,30,TFT_NAVY);

  tft.drawRect(100,180,160,30,TFT_NAVY);
  tft.fillRect(100,180,120,30,TFT_BLUE);
  
}

void loop() {
}
