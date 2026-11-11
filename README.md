Markdown
# Comunicação entre ESP32 via Protocolo MQTT

> Sistema distribuído para troca de mensagens em tempo real entre microcontroladores ESP32 utilizando o protocolo MQTT.

---

## 📋 Sobre o Projeto

Este projeto foi desenvolvido para a disciplina de [Nome da Matéria/Curso] na [Sua Facilidade/USCS], com o objetivo de implementar uma arquitetura de comunicação IoT leve e eficiente. Utilizando o protocolo MQTT, os dispositivos ESP32 conseguem publicar e assinar tópicos para trocar informações de forma descentralizada através de um Broker.

---

## 🛠️ Tecnologias e Ferramentas

* **Hardware:** [ESP32 NodeMCU / DevKit](https://github.com/ThiagoCarrascosa/Comunica-o-entre-ESP32-via-protocolo-MQTT)
* **Framework:** [PlatformIO](https://github.com/ThiagoCarrascosa/Comunica-o-entre-ESP32-via-protocolo-MQTT) (ou Arduino IDE)
* **Linguagem:** C++
* **Protocolo:** MQTT (Message Queuing Telemetry Transport)
* **Biblioteca MQTT:** PubSubClient (ou equivalente utilizada no código)

---

## ⚙️ Arquitetura e Funcionamento

```text
+----------+             +---------------+             +----------+
|  ESP32   | --(MQTT)--> | MQTT Broker   | --(MQTT)--> |  ESP32   |
| (Client) |             | (Mosquitto)   |             | (Client) |
+----------+             +---------------+             +----------+
Os dispositivos conectam-se à rede Wi-Fi configurada.

Estabelecem conexão com o Broker MQTT utilizando os parâmetros definidos.

O Dispositivo A publica mensagens em um tópico específico.

O Dispositivo B está inscrito (subscribed) no mesmo tópico e processa a mensagem recebida em tempo real.

🚀 Como Executar o Projeto
Pré-requisitos
Ter o VS Code instalado com a extensão do PlatformIO.

Acesso a uma rede Wi-Fi e a um Broker MQTT (pode ser local ou público, ex: test.mosquitto.org).

Instalação e Configuração
Clone o repositório:

Bash
git clone [https://github.com/ThiagoCarrascosa/Comunica-o-entre-ESP32-via-protocolo-MQTT.git](https://github.com/ThiagoCarrascosa/Comunica-o-entre-ESP32-via-protocolo-MQTT.git)
Abra a pasta do projeto no VS Code / PlatformIO.

Configure as suas credenciais de rede e do broker no arquivo de configuração ou diretamente no código (src/main.cpp):

C++
const char* ssid = "SEU_SSID_WIFI";
const char* password = "SUA_SENHA_WIFI";
const char* mqtt_server = "broker.hivemq.com"; // ou seu broker de preferência
Conecte o ESP32 via USB na sua máquina.

Compile e faça o upload do código utilizando o PlatformIO:

Clique no ícone de Check (Build) para compilar.

Clique no ícone de Seta para a direita (Upload) para gravar no ESP32.

📂 Estrutura do Repositório
Snippet de código
📦 
├── .vscode/          # Configurações do ambiente de desenvolvimento
├── include/          # Arquivos de cabeçalho (.h)
├── lib/              # Bibliotecas locais do projeto
├── src/              # Código-fonte principal (main.cpp)
├── test/             # Testes unitários e de integração
├── platformio.ini    # Configuração de dependências e placas do PlatformIO
└── README.md         # Documentação do projeto
✒️ Autor
Desenvolvido por Thiago de Almeida Carrascosa

