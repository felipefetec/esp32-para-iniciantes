/*
 * Projeto: Desafio — Botão cicla entre 3 LEDs coloridos
 * Livro: ESP32 Descomplicado — Capítulo 6 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Cada pressão no botão apaga o LED atual e acende o próximo
 *            na sequência: vermelho → verde → azul → vermelho...
 * Hardware: ESP32 DevKit v1 + 3 LEDs + 3 resistores 220Ω + 1 botão + protoboard
 *           LED vermelho → GPIO4  |  LED verde → GPIO5  |  LED azul → GPIO13
 *           Botão → GPIO14 e GND (pull-up interno)
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define LED_VERMELHO  4
#define LED_VERDE     5
#define LED_AZUL      13
#define PINO_BOTAO    14

// Guarda qual LED está aceso no momento.
// 0 = vermelho | 1 = verde | 2 = azul
int ledAtual = 0;

// Array com os pinos dos LEDs — facilita acender/apagar pelo índice
// em vez de usar uma cadeia de if/else para cada cor.
int pinos[] = { LED_VERMELHO, LED_VERDE, LED_AZUL };

// Função que apaga todos os LEDs de uma vez.
// Chamada antes de acender o próximo para garantir que só um fica aceso.
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

  // Começa com o LED vermelho aceso
  apagarTodos();
  digitalWrite(pinos[ledAtual], HIGH);
  Serial.println("LED vermelho ligado — pressione o botão para trocar");
}

void loop() {
  if (digitalRead(PINO_BOTAO) == LOW) {
    delay(50);  // debounce
    if (digitalRead(PINO_BOTAO) == LOW) {

      // Avança para o próximo LED na sequência.
      // O operador % (módulo) garante que após o índice 2 (azul)
      // volta para 0 (vermelho) — cria um ciclo infinito.
      ledAtual = (ledAtual + 1) % 3;

      // Apaga todos e acende apenas o LED da vez
      apagarTodos();
      digitalWrite(pinos[ledAtual], HIGH);

      // Nomes para o Serial — facilita acompanhar pelo monitor
      String nomes[] = { "vermelho", "verde", "azul" };
      Serial.println("LED " + nomes[ledAtual] + " ligado");

      // Aguarda soltar o botão
      while (digitalRead(PINO_BOTAO) == LOW);
      delay(50);
    }
  }
}
