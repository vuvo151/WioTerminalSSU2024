#include"LIS3DHTR.h"
#include"seeed_line_chart.h" 

TFT_eSPI tft;
LIS3DHTR<TwoWire>  lis;

#define MAX_SIZE 50 //maximum size of data
doubles accelerator_readings[3];
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite

void setup() {
    tft.begin();
    tft.setRotation(3);
    spr.createSprite(TFT_HEIGHT,TFT_WIDTH);
    spr.setRotation(3);

    lis.begin(Wire1);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);
}

void loop() {
    spr.fillSprite(TFT_WHITE);
    float x_raw = lis.getAccelerationX();
    float y_raw = lis.getAccelerationY();
    float z_raw = lis.getAccelerationZ();

    if (accelerator_readings[0].size() == MAX_SIZE) {
      for (uint8_t i = 0; i<3; i++){
        accelerator_readings[i].pop(); 
      }
    }
    accelerator_readings[0].push(x_raw); 
    accelerator_readings[1].push(y_raw);
    accelerator_readings[2].push(z_raw);

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value("Accelerator Readings")
                .align(center)
                .valign(vcenter)
                .width(spr.width())
                .thickness(2);

    header.height(header.font_height(&spr) * 2);
    header.draw(&spr); 

    auto content = line_chart(20, header.height());
         content
                .height(spr.height() - header.height() * 1.5)
                .width(spr.width() - content.x() * 2)
                .based_on(-2.0) 
                .show_circle(false) 
                .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2]}) 
                .max_size(MAX_SIZE)          
                .color(TFT_BLUE, TFT_RED, TFT_GREEN)
                .backgroud(TFT_WHITE)
                .draw(&spr);

    spr.pushSprite(0, 0);
    delay(50);
}