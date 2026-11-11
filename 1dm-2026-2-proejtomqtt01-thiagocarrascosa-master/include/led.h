#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
    uint8_t _pinoLed;
    bool _estadoLed = LOW;
    uint32_t _tempoAcaoAnterior_ms = 0;
    bool _estaPiscando = false;
    uint32_t _tempoEsperaAlternar_ms = 0;

    void alternar();

public:
    Led(int pino);
    
    void ligar();
    void desligar();
    void ativaPiscar(uint32_t tempoEspera = 500);
    void ativaPiscarContado(uint32_t tempoEspera, int vezes);
    void desativarPiscar();
    void iniciar();
    void atualizar();
    uint8_t getPinoLed();
    void setEstadoLed(bool estado);
};

#endif