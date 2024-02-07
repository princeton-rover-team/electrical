#pragma once
#include <Arduino.h> 
#include <Adafruit_NeoPixel.h>

class Matrix{
    Adafruit_NeoPixel strip;

public: 

    Matrix(Adafruit_NeoPixel strip) {};
    
    void write_color(bool autonomous);
};
