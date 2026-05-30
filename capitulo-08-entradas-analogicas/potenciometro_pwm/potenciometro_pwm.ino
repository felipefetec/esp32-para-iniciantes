/*
 * Projeto: Potenciômetro controla brilho do LED
 * Livro: ESP32 Descomplicado — Capítulo 8
 * Autor: Felipe Tavares
 * Descrição: Lê o valor do potenciômetro (0–4095) e usa a função map()
 *            para converter para a faixa do PWM (0–255), controlando
 *            o brilho do LED em tempo real conforme o potenciômetro é girado.
 * Hardware: ESP32 DevKit v1 + potenciômetro 10kΩ + LED + resistor 220Ω + protoboard
 *           Potenciômetro: pino central (SIG) → GPIO32 | VCC → 3,3V | GND → GND
 *           LED: anodo → resistor 220Ω → GPIO4 | catodo → GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// GPIO32 é um pino ADC1 — funciona com WiFi ativo (ao contrário dos pinos ADC2)
#define PINO_POT 32
#define PINO_LED  4

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Gire o potenciômetro para controlar o brilho do LED.");
}

void loop() {
  // analogRead retorna valor entre 0 e 4095 (12 bits no ESP32)
  int leitura = analogRead(PINO_POT);

  // map() converte a faixa 0–4095 para 0–255 (faixa do analogWrite)
  int brilho = map(leitura, 0, 4095, 0, 255);

  // Aplica o brilho ao LED via PWM
  analogWrite(PINO_LED, brilho);

  // Mostra os dois valores no Monitor Serial para acompanhar
  Serial.print("Leitura ADC: ");
  Serial.print(leitura);
  Serial.print(" | Brilho PWM: ");
  Serial.println(brilho);

  // Pequena pausa para não inundar o Monitor Serial com leituras
  delay(100);
}
