#include"LIS3DHTR.h" //include accelerometer library
LIS3DHTR<TwoWire> lis; //Initialize accelerometer

float x_val, y_val, z_val;
void setup() {
  Serial.begin(115200);
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
  Serial.println();
  delay(50); 
}