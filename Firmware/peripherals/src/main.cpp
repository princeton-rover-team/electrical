#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "matrix.h"
#include <FlexCAN_T4.h>
#include <isotp.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
CAN_message_t msg;

const int PIXEL_COUNT = 64; 
const int PIXEL_PIN = 6;

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Matrix matrix(strip);

void setup() {
  strip.begin();
  pinMode(PIXEL_PIN, OUTPUT);
  Can1.begin();
  Can1.setClock(CLK_60MHz);
  Can1.setBaudRate(95238);
  Can1.setMaxMB(16);
  Can1.enableFIFO();
  Can1.enableFIFOInterrupt();
}

void loop() {
  static uint32_t sendTimer = millis();
  if (millis() - sendTimer > 1000 ) {
    if (Can1.read(msg)) {
      Serial.print("CAN1 "); 
      Serial.print("MB: "); Serial.print(msg.mb);
      Serial.print("  ID: 0x"); Serial.print(msg.id, HEX );
      Serial.print("  EXT: "); Serial.print(msg.flags.extended );
      Serial.print("  LEN: "); Serial.print(msg.len);
      Serial.print(" DATA: ");
      for (uint8_t i = 0; i < 8; i++ ) {
        Serial.print(msg.buf[i]); Serial.print(" ");
      }
      Serial.print("  TS: "); Serial.println(msg.timestamp);
      matrix.write_color(msg.buf[0] == 1);
    sendTimer = millis();}
  }
}

