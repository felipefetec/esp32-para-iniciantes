/*
 * Projeto: Fade — LED acende e apaga gradualmente
 * Livro: ESP32 Descomplicado — Capítulo 7
 * Autor: Felipe Tavares
 * Descrição: Usa PWM para aumentar e diminuir o brilho do LED suavemente,
 *            criando o efeito de "respiração" contínua.
 * Hardware: ESP32 DevKit v1 + 1 LED + 1 resistor 220Ω + protoboard
 *           LED → resistor 220Ω → GPIO4
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED 4

// Passo de incremento do brilho a cada ciclo.
// Valores menores = transição mais suave e lenta.
// Valores maiores = transição mais rápida e brusca.
#define PASSO 5

void setup() {
  // No ESP32 core 3.x, analogWrite funciona diretamente como no Arduino Uno.
  // Não é necessário configurar canais PWM manualmente.
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Fade iniciado!");
}

void loop() {
  // Fade in: brilho de 0 (apagado) até 255 (máximo)
  for (int brilho = 0; brilho <= 255; brilho += PASSO) {
    analogWrite(PINO_LED, brilho);
    delay(15);  // pequena pausa entre cada passo — controla a velocidade do fade
  }

  // Garante que chegou ao máximo exato
  analogWrite(PINO_LED, 255);
  delay(200);  // pausa no pico antes de começar a apagar

  // Fade out: brilho de 255 (máximo) até 0 (apagado)
  for (int brilho = 255; brilho >= 0; brilho -= PASSO) {
    analogWrite(PINO_LED, brilho);
    delay(15);
  }

  // Garante que chegou ao zero exato
  analogWrite(PINO_LED, 0);
  delay(200);  // pausa no mínimo antes de começar a acender novamente
}
