#include "LED.h"
#include <Arduino.h>

Led::Led(int b_pin){
    LED_PIN = b_pin;
    pinMode(LED_PIN, OUTPUT);
    led_exec_time = 0;
    led_delay_mult = 1;
    led_delay = led_delay_mult * 1000;
    led_state = false;
}

void Led::PiscaLed(unsigned long &curr_time){
  if (curr_time - led_exec_time >= led_delay){
    
    //Atualiza o tempo da ultima execução da função do led
    led_exec_time = curr_time;

    //Inverte o estado do led
    if (led_state == true){
      led_state = false;
    }
    else{
      led_state = true;
    }

    // Serial.print(led_state);
    digitalWrite(LED_BUILTIN, led_state);
  }
}

void Led::IncDelay(unsigned long & curr_time){
  if(led_delay_mult < 5){
    led_delay_mult++;
    led_delay = led_delay_mult * 1000;
  }
  // Serial.print("Led delay: ");
  // Serial.println(led_delay);  
}

void Led::DecDelay(unsigned long & curr_time){
  if(led_delay_mult > 1){
    led_delay_mult--;
    led_delay = led_delay_mult * 1000;
  }
  // Serial.print("Led delay: ");
  // Serial.println(led_delay);  
}