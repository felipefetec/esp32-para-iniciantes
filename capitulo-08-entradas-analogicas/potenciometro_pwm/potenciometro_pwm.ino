/*
 * Projeto: Potenciômetro controla brilho do LED
 * Livro: ESP32 para Iniciantes — Capítulo 8
 * Autor: Felipe Tavares
 * Descrição: Lê o potenciômetro (0–4095) e usa map() para converter
 *            para a faixa do PWM (0–255), controlando o brilho do LED.
 * Hardware: Potenciômetro SIG → GPIO32 | VCC → 3,3V | GND → GND
 *           LED → resistor 220Ω → GPIO4 | catodo → GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// GPIO32 é ADC1 — funciona mesmo com WiFi ativo
#define PINO_POT 32
#define PINO_LED  4

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Gire o potenciômetro para controlar o brilho do LED.");
}

void loop() {
  int leitura = analogRead(PINO_POT);             // 0 a 4095
  int brilho  = map(leitura, 0, 4095, 0, 255);   // converte para 0–255
  analogWrite(PINO_LED, brilho);

  Serial.print("Leitura ADC: ");
  Serial.print(leitura);
  Serial.print(" | Brilho PWM: ");
  Serial.println(brilho);

  delay(100);
}
