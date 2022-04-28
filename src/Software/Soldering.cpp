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

    heating = false;

    curr_page = 1;
}

Soldering::~Soldering(){

}