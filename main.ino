#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include "src/bitlash.h"

#include <lwm.h>
#include <js0n.h>
#include <math.h>
#include "version.h"

void setup() {
  Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);
  // Add custom setup code here
  addBitlashFunction("spectrum.ndvi", (bitlash_function) getNdvi);
  addBitlashFunction("spectrum.ndvicolor", (bitlash_function) getNdviColor);
}


unsigned long last_t = 0;
int redPin = 0;
int bluePin = 0;
int lastColor = 0;

int ndvi_colors[] = {
  0,0,0,
  0,0,185, 
  0,0,228, 
  3,10,248, 
  3,168,255,
  2,227,255,
  1,254,3,
  182,255,8,
  255,252,0,
  255,222,0,
  255,143,0,
  254,93,3,
  243,0,0,
  239,0,187,
  223,180,233,
  255,255,255
};

void loop() {
  Scout.loop();
  // Add custom loop code here
  unsigned long t = millis();
  if( t-last_t > 2000){
    last_t = t;
    led_ndvi();
  }
  
}

static numvar getNdvi(){
  Serial.println(ndvi(),6);
}

static numvar getNdviColor(){
  int i = ndvi();
  int color = ndviColor(i);
  Serial.print("[");
  Serial.print(ndvi_colors[color]);
  Serial.print(",");
  Serial.print(ndvi_colors[color+1]);
  Serial.print(",");
  Serial.print(ndvi_colors[color+2]);
  Serial.println("]");
}

static int ndviColor(float i){
  float ndvi_percent = i*100/2;
  int color_index = round(16*ndvi_percent/100);
     
  if(color_index < 1) color_index = 1;
  if(color_index > 16) color_index = 16;
     
  Serial.print("color num:");
  Serial.println(color_index);
  
  int color_start = (color_index-1)*3;
    
  return color_start;
}

void led_ndvi(){
  float i = ndvi();
  int color = ndviColor(i);
  
  Serial.println(i,6);
  Serial.println(color);
  RgbLed.setColor(ndvi_colors[color],ndvi_colors[color+1],ndvi_colors[color+2]);
}



float ndvi(){
  bluePin = analogRead(1); 
  redPin = analogRead(0)-bluePin;
  if(redPin < 1) redPin = 1;
  // blue pin may contain a little light blue which i call noise here.
  // red pin and blue pin contain near ifrared. bluePin is almost completely near ir 700+
  
  //Serial.print("red pin: ");
  //Serial.println(redPin);

  //Serial.print("blue pin: ");
  //Serial.println(bluePin);
  //Serial.print("blue-red: ");
  //Serial.println(bluePin-redPin);
  //Serial.print("blue+red: ");
  //Serial.println(bluePin+redPin);  
  return (float)(bluePin-redPin)/(bluePin+redPin);
}
