/*
 * Projeto: Desafio — SOS em código Morse
 * Livro: ESP32 Descomplicado — Capítulo 2 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Pisca o LED embutido transmitindo SOS em código Morse:
 *            três flashes curtos (S), três longos (O), três curtos (S).
 *            Repete continuamente com pausa entre cada transmissão.
 * Hardware: ESP32 DevKit v1 (38 ou 30 pinos) — só o cabo USB
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: usar diagram.json com apenas o ESP32 (LED embutido)
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// LED embutido do ESP32 DevKit v1 — GPIO2
#define PINO_LED 2

// Duração dos elementos do código Morse em milissegundos.
// Centralizar aqui facilita ajustar o ritmo sem caçar valores no código.
#define PONTO   200   // flash curto  (· )
#define TRACO   600   // flash longo  (— )
#define GAP     200   // pausa entre flashes dentro de uma letra
#define GAP_LETRA 1000  // pausa entre letras

// Pisca o LED uma vez com a duração especificada e aguarda o gap seguinte
void flash(int duracao) {
  digitalWrite(PINO_LED, HIGH);
  delay(duracao);
  digitalWrite(PINO_LED, LOW);
  delay(GAP);  // intervalo obrigatório entre cada flash
}

// Transmite a letra S em Morse: · · ·
void letraS() {
  flash(PONTO);
  flash(PONTO);
  flash(PONTO);
  delay(GAP_LETRA);  // pausa após a letra
}

// Transmite a letra O em Morse: — — —
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
  // S — O — S
  letraS();
  letraO();
  letraS();

  // Pausa longa antes de repetir a mensagem
  delay(3000);
  Serial.println("SOS transmitido — repetindo...");
}
