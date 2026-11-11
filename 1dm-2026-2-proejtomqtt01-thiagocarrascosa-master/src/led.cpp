#include "led.h"

Led::Led(int pino) : _pinoLed(pino) {}

void Led::ligar()
{
    _estadoLed = HIGH;
}

void Led::desligar()
{
    _estadoLed = LOW;
}

void Led::ativaPiscar(uint32_t tempoEspera)
{
    _estaPiscando = true;
    _tempoEsperaAlternar_ms = tempoEspera;
    _limitePiscadas = 0; // Infinito
}

void Led::ativaPiscarContado(uint32_t tempoEspera, int vezes)
{
    _estaPiscando = true;
    _tempoEsperaAlternar_ms = tempoEspera;
    _limitePiscadas = vezes * 2; // Cada ciclo completo (liga/desliga) conta 2 transições
    _contadorPiscadas = 0;
}

void Led::iniciar()
{
    pinMode(_pinoLed, OUTPUT);
    digitalWrite(_pinoLed, LOW);
    _tempoAcaoAnterior_ms = millis();
}

void Led::alternar()
{
    _estadoLed = !_estadoLed;
    if (_limitePiscadas > 0)
    {
        _contadorPiscadas++;
        if (_contadorPiscadas >= _limitePiscadas)
        {
            _estaPiscando = false;
            _estadoLed = LOW;
        }
    }
}

void Led::desativarPiscar()
{
    _estaPiscando = false;
    _estadoLed = LOW;
}

void Led::atualizar()
{
    if (_estaPiscando)
    {
        const uint32_t tempoDecorrido = millis() - _tempoAcaoAnterior_ms;
        if (tempoDecorrido >= _tempoEsperaAlternar_ms)
        {
            _tempoAcaoAnterior_ms = millis();
            alternar();
        }
    }
    digitalWrite(_pinoLed, _estadoLed);
}

uint8_t Led::getPinoLed()
{
    return _pinoLed;
}

void Led::setEstadoLed(bool estado)
{
    _estadoLed = estado;
}