#include "matrix.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

void Matrix::write_color(bool autonomous) {
    int r;
    int g;
    int b;
    if(autonomous) {
        r = 255;
        g = 0;
        b = 0;
    }
    else{
        r = 255;
        g = 0;
        b = 0;
    }
    strip.clear();
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, r, g, b);
    }
    
}

Matrix::Matrix(Adafruit_NeoPixel strip) {
    this->strip = strip;
}






