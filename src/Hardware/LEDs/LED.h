#ifndef LED
#define LED

class Led{
    private:
        int LED_PIN;
        unsigned long led_exec_time; //Guarda a última vez quando entramos na função de piscar o led
        unsigned long led_delay_mult; //Multiplicador de segundos de intervalo do led
        unsigned long led_delay; //Tempo de delay entre as piscadas do led, em ms
        bool led_state; //Tempo de delay entre as piscadas do led, em ms

    public:
        Led(int l_pin);

        void PiscaLed(unsigned long &curr_time);

        void IncDelay(unsigned long & curr_time);
        void DecDelay(unsigned long & curr_time);
};

#endif