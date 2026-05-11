/*
 * Projeto: Desafio — Botão cicla entre 3 LEDs coloridos
 * Livro: ESP32 para Iniciantes — Capítulo 6 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Cada pressão no botão acende o próximo LED na sequência:
 *            vermelho → verde → azul → vermelho...
 * Hardware: LED vermelho → GPIO4 | LED verde → GPIO5 | LED azul → GPIO13
 *           Botão → GPIO14 e GND (pull-up interno)
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define LED_VERMELHO  4
#define LED_VERDE     5
#define LED_AZUL     13
#define PINO_BOTAO   14

int ledAtual = 0;
int pinos[]  = { LED_VERMELHO, LED_VERDE, LED_AZUL };

void apagarTodos() {
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE,    LOW);
  digitalWrite(LED_AZUL,     LOW);
}

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE,    OUTPUT);
  pinMode(LED_AZUL,     OUTPUT);
  pinMode(PINO_BOTAO,   INPUT_PULLUP);
  Serial.begin(115200);
  apagarTodos();
  digitalWrite(pinos[ledAtual], HIGH);
  Serial.println("LED vermelho ligado — pressione o botão para trocar");
}

void loop() {
  if (digitalRead(PINO_BOTAO) == LOW) {
    delay(50);
    if (digitalRead(PINO_BOTAO) == LOW) {
      // % (módulo) garante o ciclo: após índice 2 volta para 0
      ledAtual = (ledAtual + 1) % 3;
      apagarTodos();
      digitalWrite(pinos[ledAtual], HIGH);
      String nomes[] = { "vermelho", "verde", "azul" };
      Serial.println("LED " + nomes[ledAtual] + " ligado");
      while (digitalRead(PINO_BOTAO) == LOW);
      delay(50);
    }
  }
}
