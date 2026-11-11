#include "botao.h"

Botao::Botao(uint8_t pino) : _pino(pino) {}

void Botao::iniciar()
{
    pinMode(_pino, INPUT_PULLUP);
    _estadoBotao = digitalRead(_pino);
    _estadoAnteriorBotao = _estadoBotao;
}

void Botao::atualizar()
{
    _pressionou = false; 
    _soltou = false;

    _estadoBotao = digitalRead(_pino);

    if (_estadoBotao != _estadoAnteriorBotao)
    {
        _estadoAnteriorBotao = _estadoBotao;
        _ultimaMudanca_ms = millis();
        return;
    }

    if (tempoDecorrido() < _tempoDebounce_ms) return;
    if (_estadoBotao == _estadoAnteriorBotao) return;

    _estadoAnteriorBotao = _estadoBotao;

    const bool botaoPressionado = !_estadoBotao;

    botaoPressionado ? _pressionou = true : _soltou = true;
}

bool Botao::pressionou()
{
    return _pressionou;
}

bool Botao::soltou()
{
    return _soltou;
}

uint32_t Botao::tempoDecorrido()
{
    return millis() - _ultimaMudanca_ms;
}