/*
 * Projeto: Desafio — LED de alerta por temperatura
 * Livro: ESP32 para Iniciantes — Capítulo 9 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: LED vermelho se temp > 30°C, LED azul se temp < 20°C.
 * Hardware: DHT11 → GPIO15 | LED vermelho → GPIO4 | LED azul → GPIO5
 * Biblioteca: "DHT sensor library" by Adafruit
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <DHT.h>

#define PINO_DHT      15
#define TIPO_DHT      DHT11
#define LED_VERMELHO   4
#define LED_AZUL       5
#define TEMP_QUENTE   30.0
#define TEMP_FRIA     20.0

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL,     OUTPUT);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AZUL,     LOW);
  Serial.begin(115200);
  dht.begin();
  Serial.println("Monitor de temperatura iniciado!");
}

void loop() {
  delay(2000);

  float temperatura = dht.readTemperature();
  float umidade     = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler o DHT11.");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C | Status: ");

  if (temperatura > TEMP_QUENTE) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AZUL,     LOW);
    Serial.println("QUENTE");
  } else if (temperatura < TEMP_FRIA) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AZUL,     HIGH);
    Serial.println("FRIO");
  } else {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AZUL,     LOW);
    Serial.println("Normal");
  }
}
