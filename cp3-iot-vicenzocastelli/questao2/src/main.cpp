#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = ""; // Senha vazia para rede pública "Wokwi-GUEST"

// Configurações de MQTT
const char *BROKER_MQTT = "54.157.123.32"; // Endereço do broker MQTT
const int BROKER_PORT = 8080;              // Porta do broker
const char *ID_MQTT = "esp32_mqtt";
const char *TOPIC_SUBSCRIBE_COMANDOS = "ambiente/comandos_gas/93647"; // Tópico de comandos
const char *TOPIC_PUBLISH_GAS = "ambiente/sensores_gas/93647";        // Tópico de publicação de gás detectado

// Configurações de Hardware
#define PIN_MQ2 13    // Pino do sensor MQ-2 (pino digital)
#define PIN_LED 2     // Pino do LED
#define PIN_BUZZER 18 // Pino do Buzzer

// Variáveis globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
bool lastLedState = LOW;
bool lastBuzzerState = LOW;
bool lastGasDetected = false;

// Protótipos de funções
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectWiFi();
void reconnectMQTT();
void checkWiFIAndMQTT();
void checkGasDetection();

// Conectar ao Wi-Fi
void initWiFi()
{
  Serial.print("Conectando à rede Wi-Fi: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// Conectar ao Broker MQTT
void initMQTT()
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length)
{
  String msg = String((char *)payload).substring(0, length);

  JsonDocument json;
  DeserializationError error = deserializeJson(json, msg);

  if (error)
  {
    Serial.println("Falha na deserialização do JSON.");
    return;
  }

  if (json.containsKey("acionar_led"))
  {
    bool acionar_led = json["acionar_led"];
    digitalWrite(PIN_LED, acionar_led ? HIGH : LOW);
    lastLedState = acionar_led;
    Serial.printf("LED %s via comando MQTT\n", acionar_led ? "ativado" : "desativado");
  }

  if (json.containsKey("acionar_buzzer"))
  {
    bool acionar_buzzer = json["acionar_buzzer"];
    ledcWrite(0, acionar_buzzer ? 128 : 0); // Usa PWM para o buzzer
    lastBuzzerState = acionar_buzzer;
    Serial.printf("Buzzer %s via comando MQTT\n", acionar_buzzer ? "ativado" : "desativado");
  }
}

// Reconnecta ao Broker MQTT caso a conexão seja perdida
void reconnectMQTT()
{
  while (!MQTT.connected())
  {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT))
    {
      Serial.println("Conectado ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBE_COMANDOS); // Subscreve ao tópico de comandos
    }
    else
    {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

// Verificar o status do Wi-Fi e do MQTT
void checkWiFIAndMQTT()
{
  if (WiFi.status() != WL_CONNECTED)
    reconnectWiFi();
  if (!MQTT.connected())
    reconnectMQTT();
}

// Conectar ao Wi-Fi se necessário
void reconnectWiFi(void)
{
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); // Conecta na rede Wi-Fi

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wi-Fi conectado com sucesso: ");
  Serial.println(WiFi.localIP());
}

// Função para verificar a detecção de gás e publicar via MQTT
void checkGasDetection()
{
  int valorGas = digitalRead(PIN_MQ2); // Lê o valor do sensor MQ-2 (verifique se o sensor está digital)

  bool gasDetected = (valorGas == LOW); // Gás detectado quando a leitura é LOW

  // Verifica se houve mudança na detecção de gás
  if (gasDetected != lastGasDetected)
  {
    lastGasDetected = gasDetected;

    // Publica o estado de detecção de gás no tópico MQTT
    JsonDocument doc;
    doc["local"] = 'sala93647#include <Arduino.h>'
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

        // Configurações de WiFi
        const char *SSID = "Wokwi-GUEST";
    const char *PASSWORD = ""; // Senha vazia para rede pública "Wokwi-GUEST"

    // Configurações de MQTT
    const char *BROKER_MQTT = "54.157.123.32"; // Endereço do broker MQTT
    const int BROKER_PORT = 8080;              // Porta do broker
    const char *ID_MQTT = "esp32_mqtt";
    const char *TOPIC_SUBSCRIBE_COMANDOS = "ambiente/comandos_gas/93647"; // Tópico de comandos
    const char *TOPIC_PUBLISH_GAS = "ambiente/sensores_gas/93647";        // Tópico de publicação de gás detectado

// Configurações de Hardware
#define PIN_MQ2 13    // Pino do sensor MQ-2 (pino digital)
#define PIN_LED 2     // Pino do LED
#define PIN_BUZZER 18 // Pino do Buzzer

    // Variáveis globais
    WiFiClient espClient;
    PubSubClient MQTT(espClient);
    bool lastLedState = LOW;
    bool lastBuzzerState = LOW;
    bool lastGasDetected = false;

    // Protótipos de funções
    void initWiFi();
    void initMQTT();
    void callbackMQTT(char *topic, byte *payload, unsigned int length);
    void reconnectWiFi();
    void reconnectMQTT();
    void checkWiFIAndMQTT();
    void checkGasDetection();

    // Conectar ao Wi-Fi
    void initWiFi()
    {
      Serial.print("Conectando à rede Wi-Fi: ");
      Serial.println(SSID);
      WiFi.begin(SSID, PASSWORD);

      while (WiFi.status() != WL_CONNECTED)
      {
        delay(100);
        Serial.print(".");
      }

      Serial.println();
      Serial.print("Conectado com sucesso: ");
      Serial.println(SSID);
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    }

    // Conectar ao Broker MQTT
    void initMQTT()
    {
      MQTT.setServer(BROKER_MQTT, BROKER_PORT);
      MQTT.setCallback(callbackMQTT);
    }

    void callbackMQTT(char *topic, byte *payload, unsigned int length)
    {
      String msg = String((char *)payload).substring(0, length);

      JsonDocument json;
      DeserializationError error = deserializeJson(json, msg);

      if (error)
      {
        Serial.println("Falha na deserialização do JSON.");
        return;
      }

      if (json.containsKey("acionar_led"))
      {
        bool acionar_led = json["acionar_led"];
        digitalWrite(PIN_LED, acionar_led ? HIGH : LOW);
        lastLedState = acionar_led;
        Serial.printf("LED %s via comando MQTT\n", acionar_led ? "ativado" : "desativado");
      }

      if (json.containsKey("acionar_buzzer"))
      {
        bool acionar_buzzer = json["acionar_buzzer"];
        ledcWrite(0, acionar_buzzer ? 128 : 0); // Usa PWM para o buzzer
        lastBuzzerState = acionar_buzzer;
        Serial.printf("Buzzer %s via comando MQTT\n", acionar_buzzer ? "ativado" : "desativado");
      }
    }

    // Reconnecta ao Broker MQTT caso a conexão seja perdida
    void reconnectMQTT()
    {
      while (!MQTT.connected())
      {
        Serial.print("Tentando conectar com o Broker MQTT: ");
        Serial.println(BROKER_MQTT);

        if (MQTT.connect(ID_MQTT))
        {
          Serial.println("Conectado ao broker MQTT!");
          MQTT.subscribe(TOPIC_SUBSCRIBE_COMANDOS); // Subscreve ao tópico de comandos
        }
        else
        {
          Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
          delay(2000);
        }
      }
    }

    // Verificar o status do Wi-Fi e do MQTT
    void checkWiFIAndMQTT()
    {
      if (WiFi.status() != WL_CONNECTED)
        reconnectWiFi();
      if (!MQTT.connected())
        reconnectMQTT();
    }

    // Conectar ao Wi-Fi se necessário
    void reconnectWiFi(void)
    {
      if (WiFi.status() == WL_CONNECTED)
        return;

      WiFi.begin(SSID, PASSWORD); // Conecta na rede Wi-Fi

      while (WiFi.status() != WL_CONNECTED)
      {
        delay(100);
        Serial.print(".");
      }

      Serial.println();
      Serial.print("Wi-Fi conectado com sucesso: ");
      Serial.println(WiFi.localIP());
    }

    // Função para verificar a detecção de gás e publicar via MQTT
    void checkGasDetection()
    {
      int valorGas = digitalRead(PIN_MQ2); // Lê o valor do sensor MQ-2 (verifique se o sensor está digital)

      bool gasDetected = (valorGas == LOW); // Gás detectado quando a leitura é LOW

      // Verifica se houve mudança na detecção de gás
      if (gasDetected != lastGasDetected)
      {
        lastGasDetected = gasDetected;

        // Publica o estado de detecção de gás no tópico MQTT
        JsonDocument doc;
        doc["local"] = "cozinha93647"; // Insira o seu ID ou nome de local aqui
        doc["gas_detectado"] = gasDetected;

        char buffer[200];
        serializeJson(doc, buffer);
        MQTT.publish(TOPIC_PUBLISH_GAS, buffer);
        Serial.println(buffer);

        // Aciona LED e Buzzer quando o gás for detectado
        if (gasDetected)
        {
          digitalWrite(PIN_LED, HIGH); // Acende o LED
          ledcWrite(0, 128);           // Liga o Buzzer
          Serial.println("Gás detectado! LED e Buzzer acionados.");
        }
        else
        {
          digitalWrite(PIN_LED, LOW); // Desliga o LED
          ledcWrite(0, 0);            // Desliga o Buzzer
          Serial.println("Gás não detectado. LED e Buzzer desligados.");
        }
      }
    }

    // Função de inicialização do programa
    void setup()
    {
      Serial.begin(115200);

      ledcSetup(0, 1000, 8); // Canal 0, frequência 1000Hz, resolução 8 bits
      ledcAttachPin(PIN_BUZZER, 0);

      pinMode(PIN_LED, OUTPUT); // Define o pino do LED como saída
      pinMode(PIN_MQ2, INPUT);  // Define o pino do sensor MQ-2 como entrada (verifique se é digital ou analógico)

      // Inicializa Wi-Fi e MQTT
      initWiFi();
      initMQTT();
    }

    // Função loop
    void loop()
    {
      checkWiFIAndMQTT();
      MQTT.loop(); // Processa as mensagens MQTT

      // Verifica periodicamente a detecção de gás e publica via MQTT
      checkGasDetection();
    }

    {
      "acionar_led" : true,
                      "acionar_buzzer" : true
    }

    "; // Insira o seu ID ou nome de local aqui
        doc["gas_detectado"] = gasDetected;

    char buffer[200];
    serializeJson(doc, buffer);
    MQTT.publish(TOPIC_PUBLISH_GAS, buffer);
    Serial.println(buffer);

    // Aciona LED e Buzzer quando o gás for detectado
    if (gasDetected)
    {
      digitalWrite(PIN_LED, HIGH); // Acende o LED
      ledcWrite(0, 128);           // Liga o Buzzer
      Serial.println("Gás detectado! LED e Buzzer acionados.");
    }
    else
    {
      digitalWrite(PIN_LED, LOW); // Desliga o LED
      ledcWrite(0, 0);            // Desliga o Buzzer
      Serial.println("Gás não detectado. LED e Buzzer desligados.");
    }
  }
}

// Função de inicialização do programa
void setup()
{
  Serial.begin(115200);

  ledcSetup(0, 1000, 8); // Canal 0, frequência 1000Hz, resolução 8 bits
  ledcAttachPin(PIN_BUZZER, 0);

  pinMode(PIN_LED, OUTPUT); // Define o pino do LED como saída
  pinMode(PIN_MQ2, INPUT);  // Define o pino do sensor MQ-2 como entrada (verifique se é digital ou analógico)

  // Inicializa Wi-Fi e MQTT
  initWiFi();
  initMQTT();
}

// Função loop
void loop()
{
  checkWiFIAndMQTT();
  MQTT.loop(); // Processa as mensagens MQTT

  // Verifica periodicamente a detecção de gás e publica via MQTT
  checkGasDetection();
}

{
  "acionar_led" : true,
                  "acionar_buzzer" : true
}
