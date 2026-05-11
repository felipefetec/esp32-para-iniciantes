/*
 * Projeto: Desafio — SOS em código Morse
 * Livro: ESP32 para Iniciantes — Capítulo 2 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Pisca o LED embutido transmitindo SOS em código Morse:
 *            três flashes curtos (S), três longos (O), três curtos (S).
 *            Repete continuamente com pausa entre cada transmissão.
 * Hardware: ESP32 DevKit v1 (38 ou 30 pinos) — só o cabo USB
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED    2
#define PONTO     200
#define TRACO     600
#define GAP       200
#define GAP_LETRA 1000

void flash(int duracao) {
  digitalWrite(PINO_LED, HIGH);
  delay(duracao);
  digitalWrite(PINO_LED, LOW);
  delay(GAP);
}

void letraS() {
  flash(PONTO);
  flash(PONTO);
  flash(PONTO);
  delay(GAP_LETRA);
}

void letraO() {
  flash(TRACO);
  flash(TRACO);
  flash(TRACO);
  delay(GAP_LETRA);
}

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Transmitindo SOS...");
}

void loop() {
  letraS();
  letraO();
  letraS();
  delay(3000);
  Serial.println("SOS transmitido — repetindo...");
}
