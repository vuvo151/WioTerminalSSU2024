#include"LIS3DHTR.h" 
LIS3DHTR<TwoWire> lis;
#include "TFT_eSPI.h" 

TFT_eSPI tft; 
float x_val, y_val, z_val;
void setup() {
  Serial.begin(115200);

  tft.begin(); //start TFT LCD 
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE); 
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setTextColor(TFT_BLACK); 
  tft.drawString("Accelerometer Data",40,20); 

  tft.drawString("Acc_X", 40, 70);
  tft.drawString("Acc_Y", 40, 130);
  tft.drawString("Acc_Z", 40, 190);

  lis.begin(Wire1); //Start accelerometer 

  if (!lis) { 
    Serial.println("ERROR"); 
    while(1);
  }
  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G);
}
 
void loop() {
  x_val = lis.getAccelerationX();
  y_val = lis.getAccelerationY();
  z_val = lis.getAccelerationZ();
 
  Serial.print("X: "); Serial.print(x_val);
  Serial.print("Y: "); Serial.print(y_val);
  Serial.print("Z: "); Serial.print(z_val);

  tft.fillRect(160,70, 150, 25, TFT_WHITE);
  tft.drawString((String)x_val, 160, 70);

  tft.fillRect(160,130, 150, 25, TFT_WHITE);  
  tft.drawString((String)y_val, 160, 130);

  tft.fillRect(160,190, 150, 25, TFT_WHITE);
  tft.drawString((String)z_val, 160, 190);

  Serial.println();
  delay(50); 
}