/*
 * Projeto: Semáforo com 3 LEDs
 * Livro: ESP32 para Iniciantes — Capítulo 4
 * Autor: Felipe Tavares
 * Descrição: Simula um semáforo real com LED vermelho, amarelo e verde,
 *            usando #define para controlar os tempos de cada fase.
 * Hardware: LED vermelho → GPIO4 | LED amarelo → GPIO5 | LED verde → GPIO13
 *           Cada LED com resistor de 220Ω em série
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define LED_VERMELHO   4
#define LED_AMARELO    5
#define LED_VERDE     13
#define TEMPO_VERMELHO 5000
#define TEMPO_AMARELO  2000
#define TEMPO_VERDE    5000

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO,  OUTPUT);
  pinMode(LED_VERDE,    OUTPUT);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    LOW);
  Serial.begin(115200);
  Serial.println("Semáforo iniciado!");
}

void loop() {
  // Fase vermelha
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    LOW);
  Serial.println("VERMELHO — sinal fechado");
  delay(TEMPO_VERMELHO);

  // Fase amarela (abrindo)
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  HIGH);
  Serial.println("AMARELO — atenção");
  delay(TEMPO_AMARELO);

  // Fase verde
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE,   HIGH);
  Serial.println("VERDE — sinal aberto");
  delay(TEMPO_VERDE);

  // Fase amarela (fechando)
  digitalWrite(LED_VERDE,   LOW);
  digitalWrite(LED_AMARELO, HIGH);
  Serial.println("AMARELO — fechando...");
  delay(TEMPO_AMARELO);
  digitalWrite(LED_AMARELO, LOW);
}
