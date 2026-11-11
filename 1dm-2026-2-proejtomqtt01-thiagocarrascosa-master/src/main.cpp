/*
  Nome: Thiago Carrascosa
  Data: 10/11/2026
  Projeto: Comunicação entre ESP32 via protocolo MQTT
  
  Descrição: 
  - ESP A: Coleta dados da API Rick and Morty ao pressionar o botão, 
    desserializa, serializa em um documento JSON e publica em um tópico MQTT.
  - ESP B: Ao receber a mensagem, pisca o LED 3 vezes para sinalizar 
    a notificação, desserializa os dados recebidos e exibe as informações 
    em um painel LCD. 
       O mesmo ESP que recebe  executa esta mesma 
    função de envio com pequenas alterações no código.
       O ESP que envia também recebe os dados enviados pelo ESP B ,e o exibe em
       seu painel  LCD.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include "led.h"
#include "botao.h"

// Configuração do display LCD I2C (endereço 0x27, 20 colunas e 4 linhas)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Instanciação dos objetos de hardware usando POO
Led ledVerde(4);
Botao btn1(11);

// Credenciais da rede Wi-Fi
const char *SSID = "SENAI EDUCACIONAL";
const char *SENHA = "info@134";

// Configurações do Broker MQTT
const char *BROKER = "broker.emqx.io";
const int PORTA = 1883;
const char *TOPICO_SUB = "senai134/esp32/thiago.davi/status";
const char *TOPICO_PUB = "senai134/esp32/thiago.davi/comando";

WiFiClient WifiCliente;
PubSubClient mqtt(WifiCliente);

// Assinaturas das funções utilizadas no código
void aoReceber(char *topico, uint8_t *payLoad, unsigned int tamanho);
void tratarJson(String mensagem);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  
  // Inicializa o display LCD
  lcd.init();
  lcd.backlight();

  // Inicializa os pinos dos componentes via POO
  ledVerde.iniciar();
  btn1.iniciar();

  // Conexão com a rede Wi-Fi
  Serial.printf("Conectando na rede %s", SSID);
  WiFi.begin(SSID, SENHA);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.printf("\n\rConectado a rede %s com sucesso\n\r", SSID);

  // Configuração e conexão com o servidor MQTT
  mqtt.setServer(BROKER, PORTA);
  mqtt.setCallback(aoReceber);

  // Gera um ID único para o ESP32 baseado no endereço MAC
  String id = "esp32-" + String((uint32_t)ESP.getEfuseMac(), HEX);

  if (mqtt.connect(id.c_str()))
  {
    Serial.printf("\n\rConectado ao broker %s com sucesso!\n\r", BROKER);
    mqtt.subscribe(TOPICO_PUB);
  }
  else
  {
    Serial.printf("Falha ao conectar ao broker %s\n\r", BROKER);
    Serial.print("Falha: ");
    Serial.println(mqtt.state());
  }
}


void loop()
{
  // Mantém a conexão com o broker MQTT ativa
  mqtt.loop();
  
  // Atualiza os estados de forma assíncrona usando millis()
  ledVerde.atualizar();
  btn1.atualizar();

  // Se o botão for pressionado, aciona o LED localmente
  if (btn1.pressionou())
  {
    ledVerde.ativaPiscar(100);
  }
}


// Função chamada automaticamente ao receber uma nova mensagem MQTT
void aoReceber(char *topico, uint8_t *payLoad, unsigned int tamanho)
{
  String mensagem;
  mensagem.reserve(tamanho);

  for (unsigned int i = 0; i < tamanho; i++)
  {
    mensagem += (char)payLoad[i];
  }

  Serial.printf("Mensagem recebida no topico: %s \n\r mensagem: %s \n\r", topico, mensagem.c_str());
  tratarJson(mensagem);
}


// Processa o JSON recebido, atualiza o display e pisca o LED 3 vezes
void tratarJson(String mensagem)
{
  JsonDocument docRick;
  JsonDocument docFiltro;

  // Filtra apenas os campos necessários para economizar memória
  docFiltro["id"] = true;
  docFiltro["nome"] = true;
  docFiltro["status"] = true;
  docFiltro["especie"] = true;
  docFiltro["estadoLed"] = true;

  DeserializationError erroJson = deserializeJson(
      docRick,
      mensagem,
      DeserializationOption::Filter(docFiltro));

  if (erroJson) return;

  // Extrai os dados do documento JSON
  String idPersonagem = docRick["id"].as<String>();
  String nomePersonagem = docRick["nome"].as<String>();
  String statusPersonagem = docRick["status"].as<String>();
  String especiePersonagem = docRick["especie"].as<String>();

  // Ao chegar mensagem, faz o LED piscar 3 vezes e parar automaticamente
  ledVerde.ativaPiscarContado(200, 3);

  // Exibe as informações atualizadas no display LCD 20x4
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID Dupla: ");
  lcd.print(idPersonagem);

  lcd.setCursor(0, 1);
  lcd.print((String("Nome: ") + nomePersonagem).substring(0, 20));

  lcd.setCursor(0, 2);
  lcd.print((String("Status: ") + statusPersonagem).substring(0, 20));

  lcd.setCursor(0, 3);
  lcd.print((String("Especie: ") + especiePersonagem).substring(0, 20));
}