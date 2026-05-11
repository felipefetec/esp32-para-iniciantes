/*
 * Projeto: Blink com Monitor Serial
 * Livro: ESP32 para Iniciantes — Capítulo 3
 * Autor: Felipe Tavares
 * Descrição: Pisca o LED embutido e envia mensagens pelo Monitor Serial,
 *            mostrando o estado atual do LED a cada mudança.
 * Hardware: ESP32 DevKit v1 (38 ou 30 pinos) — só o cabo USB, sem componentes extras
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montagem não necessária — usa apenas o LED embutido da placa
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// Pino do LED embutido no ESP32 DevKit v1.
// Usamos #define em vez de "int PINO_LED = 2" porque #define não ocupa
// memória RAM — o compilador substitui o nome pelo valor antes de compilar.
// Para constantes em microcontroladores, sempre prefira #define.
#define PINO_LED 2

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  Serial.println("ESP32 iniciado! Começando o blink...");
}

void loop() {
  digitalWrite(PINO_LED, HIGH);
  Serial.println("LED ligado");
  delay(1000);
  digitalWrite(PINO_LED, LOW);
  Serial.println("LED desligado");
  delay(1000);
}
