/*
 * Projeto: Desafio — LED de alerta por temperatura
 * Livro: ESP32 Descomplicado — Capítulo 9 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Lê temperatura do DHT11 e acende LEDs de acordo:
 *            LED vermelho se temperatura > 30°C
 *            LED azul     se temperatura < 20°C
 *            Ambos apagados se temperatura entre 20°C e 30°C
 * Hardware: ESP32 DevKit v1 + DHT11 + 2 LEDs + 2 resistores 220Ω
 *           DHT11 dados → GPIO15 | LED vermelho → GPIO4 | LED azul → GPIO5
 * Bibliotecas: "DHT sensor library" by Adafruit
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <DHT.h>

#define PINO_DHT      15
#define TIPO_DHT      DHT11
#define LED_VERMELHO   4   // alerta de calor
#define LED_AZUL       5   // alerta de frio

// Limites de temperatura para acionar os alertas
#define TEMP_QUENTE   30.0
#define TEMP_FRIA     20.0

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL,     OUTPUT);

  // Garante que os LEDs começam apagados
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
    Serial.println("Erro ao ler o DHT11. Verifique a conexão.");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C  |  Umidade: ");
  Serial.print(umidade);
  Serial.print(" %  |  Status: ");

  // Lógica dos alertas — apenas um LED acende por vez
  if (temperatura > TEMP_QUENTE) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AZUL,     LOW);
    Serial.println("QUENTE - LED vermelho");
  } else if (temperatura < TEMP_FRIA) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AZUL,     HIGH);
    Serial.println("FRIO - LED azul");
  } else {
    // Temperatura confortável — apaga os dois
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AZUL,     LOW);
    Serial.println("Normal - LEDs apagados");
  }
}
