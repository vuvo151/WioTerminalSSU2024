#include"LIS3DHTR.h"
#include"seeed_line_chart.h"

TFT_eSPI tft;
LIS3DHTR<TwoWire>  lis; 
 
#define max_size 50 
doubles accelerator_readings[3]; 
TFT_eSprite spr = TFT_eSprite(&tft);
 
void setup() {
    tft.begin();
    tft.setRotation(3); 
    spr.createSprite(TFT_HEIGHT,TFT_WIDTH); 
 
    lis.begin(Wire1); 
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);
 
    Serial.begin(115200);
}
 
void loop() {
    spr.fillSprite(TFT_WHITE); //fill background 
    
    float x_raw = lis.getAccelerationX();
    float y_raw = lis.getAccelerationY();
    float z_raw = lis.getAccelerationZ();
 
    if (accelerator_readings[0].size() == max_size) {
      for (uint8_t i = 0; i<3; i++){
        accelerator_readings[i].pop();
      }
    }
    accelerator_readings[0].push(x_raw);
    accelerator_readings[1].push(y_raw);
    accelerator_readings[2].push(z_raw);
 
    auto header =  text(0, 0) //starting coordinates of text 
                .value("Acceleration Readings") //text string 
                .align(center) //horizontal alignment
                .valign(vcenter) //vertical alignment 
                .width(tft.width()) //width of title header 
                .thickness(2); //font size 
 
    header.height(header.font_height() * 2); //height of title header
    header.draw(); //Header height is twice the height of the font
 
  //Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
         content
                .height(tft.height() - header.height() * 1.5)
                .width(tft.width() - content.x() * 2)
                .based_on(-2.0) //Starting point of y-axis, must be a float
                .show_circle(false) //drawing a cirle at each point, default is on
                .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2]}) 
                .color(TFT_BLUE, TFT_RED, TFT_GREEN)
                .draw(); //draw line graph 
 
    spr.pushSprite(0, 0); //push to LCD
    delay(50);
}