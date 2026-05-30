/*
 * Projeto: Desafio — WiFi com LED de status e cronômetro
 * Livro: ESP32 Descomplicado — Capítulo 10 (Desafio 1)
 * Autor: Felipe Tavares
 * Hardware: ESP32 DevKit v1 | LED vermelho → GPIO4 com resistor 220Ω → GND
 * Biblioteca: WiFi.h (já inclusa no pacote ESP32 da Arduino IDE)
 *
 * LED pisca durante cada tentativa de conexão.
 * Após conectar, o Monitor Serial exibe quanto tempo levou.
 * LED apaga quando a conexão é estabelecida.
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <WiFi.h>

const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

#define PINO_LED 4

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);

  delay(1000);
  Serial.println("=== Conectando ao WiFi com LED de status ===");

  conectarWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão perdida. Reconectando...");
    conectarWifi();
  }

  Serial.print("IP atual: ");
  Serial.println(WiFi.localIP());
  delay(5000);
}

void conectarWifi() {
  WiFi.begin(SSID, SENHA);

  Serial.print("Conectando");

  // Guarda o tempo antes de começar — millis() conta milissegundos desde o boot
  unsigned long inicio = millis();

  // Enquanto não conectar: pisca o LED e exibe ponto no monitor
  while (WiFi.status() != WL_CONNECTED) {
    // Liga o LED por 250ms, desliga por 250ms — total 500ms por tentativa
    digitalWrite(PINO_LED, HIGH);
    delay(250);
    digitalWrite(PINO_LED, LOW);
    delay(250);

    Serial.print(".");
  }

  // Calcula quanto tempo levou em segundos
  unsigned long duracao = (millis() - inicio) / 1000;

  // Apaga o LED — conexão estabelecida
  digitalWrite(PINO_LED, LOW);

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("Tempo de conexão: ");
  Serial.print(duracao);
  Serial.println(" segundos");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}
