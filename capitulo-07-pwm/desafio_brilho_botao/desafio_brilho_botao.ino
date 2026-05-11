/*
 * Projeto: Desafio — Dois botões controlam o brilho do LED
 * Livro: ESP32 para Iniciantes — Capítulo 7 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Botão + aumenta o brilho em 25 a cada pressão.
 *            Botão - diminui o brilho em 25. Faixa: 0 a 255.
 * Hardware: LED → GPIO4 | Botão + → GPIO14 e GND | Botão - → GPIO27 e GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED       4
#define BOTAO_AUMENTAR 14
#define BOTAO_DIMINUIR 27
#define PASSO          25

int brilho = 128;  // começa na metade

// Lê um botão com debounce — retorna true se houve clique válido
bool botaoPressionado(int pino) {
  if (digitalRead(pino) == LOW) {
    delay(50);
    if (digitalRead(pino) == LOW) {
      while (digitalRead(pino) == LOW);
      delay(50);
      return true;
    }
  }
  return false;
}

void setup() {
  pinMode(PINO_LED,       OUTPUT);
  pinMode(BOTAO_AUMENTAR, INPUT_PULLUP);
  pinMode(BOTAO_DIMINUIR, INPUT_PULLUP);
  analogWrite(PINO_LED, brilho);
  Serial.begin(115200);
  Serial.println("Brilho inicial: 128/255");
  Serial.println("Botão + (GPIO14) = aumentar | Botão - (GPIO27) = diminuir");
}

void loop() {
  if (botaoPressionado(BOTAO_AUMENTAR)) {
    brilho = min(255, brilho + PASSO);  // não ultrapassa 255
    analogWrite(PINO_LED, brilho);
    Serial.print("Brilho: ");
    Serial.println(brilho);
  }
  if (botaoPressionado(BOTAO_DIMINUIR)) {
    brilho = max(0, brilho - PASSO);  // não vai abaixo de 0
    analogWrite(PINO_LED, brilho);
    Serial.print("Brilho: ");
    Serial.println(brilho);
  }
}
