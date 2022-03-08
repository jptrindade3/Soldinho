#include <Arduino.h>
#include "Hardware/Botao/Button.h"
#include "Hardware/LEDs/LED.h"
#include "Software/Soldering.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "ssd1306.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Globals
unsigned long curr_time = 0; //Responsável por pegar o tempo a cada volta do loop
unsigned long curr_antes = 0;
unsigned long curr_depois = 0;
unsigned long diff = 0;


Soldering soldinho;
Button Btn_Up(8, 1);
Button Btn_Down(9, 1);
Button Tilt_sensor(7, 5);
Led Onboard(13);

void setup() {
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.clearDisplay();
  // Wire.setClock(400000);
  Serial.begin(9600); //Define baud rate



  /* Replace the line below with the display initialization function, you want to use */
    ssd1306_128x32_i2c_init();
    ssd1306_clearScreen();
    /* Set font to use with console */
    ssd1306_setFixedFont(ssd1306xled_font6x8);
}

int antes = 0;

void loop() {
  curr_time = millis();

  // Btn_Up.CicleNHoldClick(curr_time);
  // if(Btn_Up.cicle_press == true){
  //   Onboard.IncDelay(curr_time);
  //   // Serial.println(Btn_Up.pressed);  
  //   Btn_Up.cicle_press = false;
  // }

  // Btn_Down.CicleNHoldClick(curr_time);
  // if(Btn_Down.cicle_press == true){
  //   Onboard.DecDelay(curr_time);
  //   // Serial.println(Btn_Down.pressed);  
  //   Btn_Down.cicle_press = false;
  // }
  soldinho.SetTargetTemp(Btn_Up, Btn_Down, curr_time);

  Tilt_sensor.TiltSensing(curr_time);
  
  Onboard.PiscaLed(curr_time);
  // if(soldinho.temp_now != antes){
  //   // curr_antes = millis();
  //   display.clearDisplay();
  //   // antes = soldinho.temp_now;
  //   display.setTextSize(2);
  //   display.setTextColor(WHITE);
  //   display.setCursor(0,0);
  //   display.print("Temp: ");
  //   display.print(soldinho.temp_now);
  //   display.println("C");
  //   display.display();
  //   // curr_depois = millis();
  //   // diff = curr_depois - curr_antes;
  //   // Serial.println(diff);
  // }

  if(soldinho.temp_now != antes){
    // curr_antes = millis();
    // antes = soldinho.temp_now;
    ssd1306_clearScreen();
    ssd1306_print( "This is console output: " );
    ssd1306_print( "go to the next line" );
    antes = soldinho.temp_now;
    // curr_depois = millis();
    // diff = curr_depois - curr_antes;
    // Serial.println(diff);
  }
}