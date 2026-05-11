/*
 * Projeto: Estação climática no Monitor Serial
 * Livro: ESP32 para Iniciantes — Capítulo 9
 * Autor: Felipe Tavares
 * Descrição: Lê temperatura e umidade do DHT11 e exibe no Monitor Serial.
 * Hardware: DHT11 dados → GPIO15 | VCC → 3,3V | GND → GND
 * Biblioteca: "DHT sensor library" by Adafruit
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <DHT.h>

#define PINO_DHT  15
#define TIPO_DHT  DHT11  // trocar para DHT22 ao simular no Wokwi

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("Estação climática iniciada!");
}

void loop() {
  delay(2000);  // DHT11 precisa de pelo menos 1s entre leituras

  float temperatura = dht.readTemperature();
  float umidade     = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro: não foi possível ler o sensor DHT11.");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C  |  Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
}
