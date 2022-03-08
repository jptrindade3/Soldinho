#include "Soldering.h"
#include <Arduino.h>
#include "../Hardware/Botao/Button.h"

Soldering::Soldering(){
    //PID
    Kp = 1;
    Ki = 2;
    Kd = 3;

    temp_max = 480;
    temp_min = 200;
    temp_now = temp_min;
    celcius = true;

    sleep_time = (5 * 60);

    num_pags = 2;
}

void Soldering::SetTargetTemp(Button & btn_up, Button & btn_down, unsigned long & curr_time){
    // static int counter = 0;
    btn_up.CicleNHoldClick(curr_time);
    if(btn_up.cicle_press == true){
        if(temp_max > temp_now){
            temp_now = temp_now + 10;
        }
        // Serial.println(counter ++);  
        btn_up.cicle_press = false;
    }

    btn_down.CicleNHoldClick(curr_time);
    if(btn_down.cicle_press == true){
        if(temp_min < temp_now){
            temp_now = temp_now - 10;
        }
        btn_down.cicle_press = false;
        // Serial.println(Btn_Down.pressed);  
    }
}