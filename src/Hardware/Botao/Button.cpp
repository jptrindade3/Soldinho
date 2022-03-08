#include "Button.h"
#include <Arduino.h>

Button::Button(int b_pin, unsigned long hld_time){
    BUTTON_PIN = b_pin;
    hold_time = hld_time * 1000;
    pinMode(BUTTON_PIN, INPUT);
    last_change_time = 0; // Conta, em ms, a passagem de tempo desde o clique do botão até atingir o debounce_time
    change_locker = false;
    tilted = false;
    sleeping = false;
}

void Button::CicleNHoldClick(unsigned long & curr_time){
    curr_btn_state = digitalRead(BUTTON_PIN);
    if(curr_time - last_change_time >= debounce_time){
        if(curr_btn_state == true && last_btn_state == false){
            last_change_time = curr_time;
            pressed = true;
            holding = false;
            cicle_press = true;
        }
        else if(curr_time - last_change_time >= hold_time && pressed == true && change_locker == false){
            holding = true;
            change_locker = true;
            Serial.println("Segurado");
        }
        else if(curr_btn_state == false && last_btn_state == true){
            last_change_time = curr_time;
            pressed = false;
            holding = false;
            change_locker = false;
        }
        else{
            cicle_press = false;
        }
        last_btn_state = curr_btn_state;
    }
    // Serial.println(pressed);  
}

void Button::TiltSensing(unsigned long & curr_time){
    // static int tilt = 0;
    curr_btn_state = digitalRead(BUTTON_PIN);
    if(curr_time - last_change_time >= debounce_time){
        if(curr_btn_state != last_btn_state){
            last_change_time = curr_time;
            // Serial.print("Mexeu: ");
            // Serial.println(tilt);
            // tilt++;
            tilted = true;
            sleeping = false;
            change_locker = false;
        }
        else{
            tilted = false;
        }
    }

    if(tilted == false && curr_time - last_change_time >= hold_time && change_locker == false){
            change_locker = true;
            sleeping = true;
            Serial.println("Durma amigo");
    }
    last_btn_state = curr_btn_state;
}