#ifndef SOLDERING
#define SOLDERING

#include "../Hardware/Botao/Button.h" //4102 5678

class Soldering{
    private:
    
    public:
        //PID
        float Kp;
        float Ki;
        float Kd;

        //Temperature
        int temp_max;
        int temp_min;
        int temp_now;
        bool heating;
        bool celcius;
        bool fahrenheit;

        //Time
        unsigned long sleep_time;

        //Pages
        int num_pags;
        int curr_page;

        //Others
        bool left_handed;

        Soldering();
        ~Soldering();
    
};

#endif