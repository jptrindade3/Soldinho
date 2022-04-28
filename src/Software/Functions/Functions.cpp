#include "ssd1306.h"

#include "Functions.h"

#include "Hardware/Botao/Button.h"
#include "Software/Soldering.h"

Soldering soldinho;
Button Btn_Up(8, 1);
Button Btn_Down(9, 1);
Button Tilt_sensor(7, 5);

void PageControl(unsigned long & curr_time){
    static int curr_page = 1;

    if(curr_page != soldinho.curr_page){
        ssd1306_clearScreen();
        curr_page = soldinho.curr_page;
    }

    if(soldinho.curr_page == 1){
        OptionScreen(curr_time);
    }
    else if(soldinho.curr_page == 2){
        TemperatureVisualization(curr_time);
    }
    else if(soldinho.curr_page == 3){
        SleepScreen(curr_time);
    }
}

void TemperatureVisualization(unsigned long & curr_time){
    static int curr_temp = 0;
    static char text[20];

    Tilt_sensor.TiltSensing(curr_time);

    Btn_Up.CicleNHoldClick(curr_time);
    if(Btn_Up.cicle_press == true){
        if(soldinho.temp_max > soldinho.temp_now){
            soldinho.temp_now = soldinho.temp_now + 10;
        }
        // Serial.println(counter ++);  
        Btn_Up.cicle_press = false;
    }

    Btn_Down.CicleNHoldClick(curr_time);
    if(Btn_Down.cicle_press == true){
        if(soldinho.temp_min < soldinho.temp_now){
            soldinho.temp_now = soldinho.temp_now - 10;
        }
        Btn_Down.cicle_press = false;
        // Serial.println(Btn_Down.pressed);  
    }

    if(soldinho.temp_now != curr_temp){
        curr_temp = soldinho.temp_now;
        // ssd1306_clearScreen();
        sprintf(text, "Temperatura alvo:");
        ssd1306_printFixedN(0, 0, text, STYLE_NORMAL, FONT_SIZE_NORMAL);
        sprintf(text, "%3dC", soldinho.temp_now);
        ssd1306_printFixedN(0, 16, text, STYLE_NORMAL, FONT_SIZE_2X);
    }

    if(Btn_Up.holding == true && Btn_Down.holding == true){
        Serial.println("segurou os 2");
        soldinho.curr_page = 1;
        curr_temp = 0;
    }

    if(Tilt_sensor.sleeping == true){
        soldinho.curr_page = 3;
        curr_temp = 0;
    }
}

void OptionScreen(unsigned long & curr_time){
    static char text[20];
    static int opt = 1;
    static bool on_page = false;

    Btn_Up.CicleNHoldClick(curr_time);
    if(Btn_Up.cicle_press == true){
        opt = opt + 1;
        if(opt == 3){
            opt = 1;
        }
    }
    Btn_Down.CicleNHoldClick(curr_time);
    if(Btn_Down.cicle_press == true){
        opt = opt - 1;
        if(opt == 0){
            opt = 2;
        }
    }

    if(opt == 1){
        sprintf(text, "Soldar <");
        ssd1306_printFixedN(0, 0, text, STYLE_NORMAL, FONT_SIZE_2X);
        sprintf(text, "Config  ");
        ssd1306_printFixedN(0, 16, text, STYLE_NORMAL, FONT_SIZE_2X);
    }
    else if(opt == 2){
        sprintf(text, "Soldar  ");
        ssd1306_printFixedN(0, 0, text, STYLE_NORMAL, FONT_SIZE_2X);
        sprintf(text, "Config <");
        ssd1306_printFixedN(0, 16, text, STYLE_NORMAL, FONT_SIZE_2X);
    }

    if(Btn_Up.holding == true && Btn_Down.holding == true){
        Serial.println("segurou os 2");
        if(opt == 1){
            soldinho.curr_page = 2;
        }
    }
}

void SleepScreen(unsigned long & curr_time){
    Tilt_sensor.TiltSensing(curr_time);
    static char text[20];
    static bool on_page = false;

    
    if(on_page == false){
        sprintf(text, "Sleeping");
        ssd1306_printFixedN(0, 16, text, STYLE_NORMAL, FONT_SIZE_2X);
        on_page = true;
    }

    if(Tilt_sensor.sleeping == false){
        soldinho.curr_page = 2;
        on_page = false;
    }
}
