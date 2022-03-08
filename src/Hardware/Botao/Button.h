#ifndef BUTTON
#define BUTTON

class Button{
    private:
        int BUTTON_PIN; //Define o pino de leitura no botão do arduíno
        unsigned long debounce_time = 50; // Tempo, em ms, definido para evitar o problema de bouncing (instabilidade transitória no sinal do botão)
        unsigned long last_change_time; // Salva a última vez que o botão foi apertado ou soltado
        bool change_locker; // só permite o comando de hold quando estiver destravado (false)

        bool curr_btn_state; //Captura o estado atual do botão (apertado ou não)
        bool last_btn_state; //Captura o estado anterior do botão (apertado ou não)

        bool pressed; // Retorna verdadeiro se o botão for apertado, falso se ele for solto

        unsigned long hold_time; // Tempo, em ms, definido para evitar o problema de bouncing (instabilidade transitória no sinal do botão)
        bool holding; // Retorna verdadeiro se o botão for segurado

        bool tilted;
        bool last_tilted_state;
        bool sleeping;

    public:
        bool cicle_press;

        //-----|    CONSTRUTOR & DESTRUTOR  |-----//
        Button(int b_pin, unsigned long hold_mult); //Cons
        // ~Button(); //Des

        //-----|    FUNÇÃO DE CICLE CLICK COM DETECÇÃO DE HOLD  |-----//
        /*
            Essa função detecta o clique no botão e só considera a conclusão
            do clique quando completamos um "ciclo de apertamento" (ex: apertamos
            o botão, mas a ação só é executada ao soltarmos ele novamente).
            Além disso, caso o botão seja apertado por mais de um determinado
            tempo, ele indica o Hold do botão.
        */

        void CicleNHoldClick(unsigned long & curr_time);

        void TiltSensing(unsigned long & curr_time);
};

//Inicializa o contador de delay do botão em 0ms
// unsigned long Button::last_change_time = 0.0;

#endif