/*
 * Projeto: Desafio — Três LEDs em sequência (efeito dominó)
 * Livro: ESP32 para Iniciantes — Capítulo 3 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Acende e apaga três LEDs externos um após o outro,
 *            criando um efeito de onda contínua.
 * Hardware: ESP32 DevKit v1 + 3 LEDs + 3 resistores de 220Ω + protoboard
 *           LED 1 → GPIO4 | LED 2 → GPIO5 | LED 3 → GPIO13
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// #define não ocupa memória RAM — o compilador substitui antes de compilar
#define LED1 4
#define LED2 5
#define LED3 13
#define TEMPO_ACESO 300

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  // Garante estado inicial limpo
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() {
  // Acende cada LED em sequência, aguarda e apaga antes do próximo
  digitalWrite(LED1, HIGH);
  delay(TEMPO_ACESO);
  digitalWrite(LED1, LOW);

  digitalWrite(LED2, HIGH);
  delay(TEMPO_ACESO);
  digitalWrite(LED2, LOW);

  digitalWrite(LED3, HIGH);
  delay(TEMPO_ACESO);
  digitalWrite(LED3, LOW);

  // Pausa antes de reiniciar — sem ela a animação fica contínua demais
  delay(150);
}
