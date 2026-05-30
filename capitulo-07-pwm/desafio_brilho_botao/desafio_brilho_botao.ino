/*
 * Projeto: Desafio — Dois botões controlam o brilho do LED
 * Livro: ESP32 Descomplicado — Capítulo 7 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Botão 1 aumenta o brilho do LED em 25 a cada pressão.
 *            Botão 2 diminui o brilho em 25. Faixa: 0 (apagado) a 255 (máximo).
 * Hardware: ESP32 DevKit v1 + 1 LED + 1 resistor 220Ω + 2 botões + protoboard
 *           LED → resistor 220Ω → GPIO4
 *           Botão + (aumentar) → GPIO14 e GND
 *           Botão - (diminuir) → GPIO27 e GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED        4
#define BOTAO_AUMENTAR  14
#define BOTAO_DIMINUIR  27

// Quanto o brilho muda a cada pressão (de 0 a 255)
#define PASSO 25

// Brilho atual — começa na metade para ter espaço para aumentar e diminuir
int brilho = 128;

void setup() {
  pinMode(PINO_LED,       OUTPUT);
  pinMode(BOTAO_AUMENTAR, INPUT_PULLUP);
  pinMode(BOTAO_DIMINUIR, INPUT_PULLUP);

  // Define o brilho inicial
  analogWrite(PINO_LED, brilho);

  Serial.begin(115200);
  Serial.println("Brilho inicial: 128/255");
  Serial.println("Botão + (GPIO14) = aumentar | Botão - (GPIO27) = diminuir");
}

// Função que lê um botão com debounce e retorna true se foi pressionado
bool botaoPressionado(int pino) {
  if (digitalRead(pino) == LOW) {
    delay(50);  // debounce
    if (digitalRead(pino) == LOW) {
      while (digitalRead(pino) == LOW);  // aguarda soltar
      delay(50);
      return true;  // confirma que foi um clique válido
    }
  }
  return false;  // não houve pressão
}

void loop() {
  if (botaoPressionado(BOTAO_AUMENTAR)) {
    // Aumenta o brilho, mas não ultrapassa 255 (máximo do analogWrite)
    brilho = min(255, brilho + PASSO);
    analogWrite(PINO_LED, brilho);
    Serial.print("Brilho: ");
    Serial.println(brilho);
  }

  if (botaoPressionado(BOTAO_DIMINUIR)) {
    // Diminui o brilho, mas não vai abaixo de 0 (LED apagado)
    brilho = max(0, brilho - PASSO);
    analogWrite(PINO_LED, brilho);
    Serial.print("Brilho: ");
    Serial.println(brilho);
  }
}
