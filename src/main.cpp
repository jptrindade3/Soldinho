#include <Arduino.h>

#include "Hardware/Botao/Button.h"
#include "Hardware/LEDs/LED.h"
#include "Software/Soldering.h"
#include "Software/Functions/Functions.h"

#include "ssd1306.h"
#include <Wire.h>
#include <SPI.h>


// Globals
unsigned long curr_time = 0; //Responsável por pegar o tempo a cada volta do loop


void setup() {
  Serial.begin(9600); //Define baud rate

  ssd1306_128x32_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  ssd1306_flipHorizontal(0);
  ssd1306_flipVertical(0);
}

int antes = 0, curr_page = 1;

void loop() {
  curr_time = millis();

  PageControl(curr_time);

}