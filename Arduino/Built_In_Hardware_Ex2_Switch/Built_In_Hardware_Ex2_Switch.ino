#include "TFT_eSPI.h" 
TFT_eSPI tft; //initialize TFT LCD 

void setup() {
  pinMode(WIO_5S_UP, INPUT);
  pinMode(WIO_5S_DOWN, INPUT);
  pinMode(WIO_5S_LEFT, INPUT);
  pinMode(WIO_5S_RIGHT, INPUT);
  pinMode(WIO_5S_PRESS, INPUT);

  tft.begin(); //start TFT LCD 
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE); 
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setTextColor(TFT_BLACK); 
  tft.drawString("Built-In Switch - Status",20,40);  

  tft.drawCircle(90,150,25,TFT_BLACK);  // LEFT 
  tft.drawCircle(160,150,25,TFT_BLACK); // CENTER or PRESS
  tft.drawCircle(230,150,25,TFT_BLACK); // RIGHT
  tft.drawCircle(160,90,25,TFT_BLACK);  // UP 
  tft.drawCircle(160,210,25,TFT_BLACK); // DOWN 
  
}

void loop() {
  if(digitalRead(WIO_5S_UP) == 0) {  // UP 
    tft.fillCircle(160,90,22,TFT_YELLOW);  // UP 
    delay(1000);
  }
  else if(digitalRead(WIO_5S_DOWN) == 0) {  // DOWN 
    tft.fillCircle(160,210,22,TFT_YELLOW); // DOWN 
    delay(1000);
  }
  else if(digitalRead(WIO_5S_LEFT) == 0) {  // LFET
    tft.fillCircle(90,150,22,TFT_YELLOW);  // LEFT 
    delay(1000);
  }
  else if(digitalRead(WIO_5S_RIGHT) == 0) {  // RIGHT 
    tft.fillCircle(230,150,22,TFT_YELLOW); // RIGHT
    delay(1000);
  }
  else if(digitalRead(WIO_5S_PRESS) == 0) {  // CENTER or PRESS 
    tft.fillCircle(160,150,22,TFT_YELLOW); // CENTER or PRESS
    delay(1000);
  }
  else {
    tft.fillCircle(90,150,22,TFT_WHITE);  // LEFT 
    tft.fillCircle(160,150,22,TFT_WHITE); // CENTER or PRESS
    tft.fillCircle(230,150,22,TFT_WHITE); // RIGHT
    tft.fillCircle(160,90,22,TFT_WHITE);  // UP 
    tft.fillCircle(160,210,22,TFT_WHITE); // DOWN 
  }
}
