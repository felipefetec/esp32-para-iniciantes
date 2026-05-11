/*
 * Projeto: Fade — LED acende e apaga gradualmente
 * Livro: ESP32 para Iniciantes — Capítulo 7
 * Autor: Felipe Tavares
 * Descrição: Usa PWM para criar efeito de respiração contínua no LED.
 *            analogWrite usa resolução 8 bits (0–255) por padrão no core 3.x.
 * Hardware: LED → resistor 220Ω → GPIO4
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED 4
// Passo menor = transição mais suave; passo maior = mais rápido
#define PASSO    5

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Fade iniciado!");
}

void loop() {
  // Fade in: 0 (apagado) → 255 (máximo)
  for (int brilho = 0; brilho <= 255; brilho += PASSO) {
    analogWrite(PINO_LED, brilho);
    delay(15);
  }
  analogWrite(PINO_LED, 255);
  delay(200);

  // Fade out: 255 (máximo) → 0 (apagado)
  for (int brilho = 255; brilho >= 0; brilho -= PASSO) {
    analogWrite(PINO_LED, brilho);
    delay(15);
  }
  analogWrite(PINO_LED, 0);
  delay(200);
}
