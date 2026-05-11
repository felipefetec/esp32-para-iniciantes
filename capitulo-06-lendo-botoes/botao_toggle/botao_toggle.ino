/*
 * Projeto: Botão liga/desliga LED (toggle)
 * Livro: ESP32 para Iniciantes — Capítulo 6
 * Autor: Felipe Tavares
 * Descrição: Cada pressão no botão alterna o estado do LED entre ligado
 *            e desligado. Usa pull-up interno do ESP32 e debounce por delay.
 * Hardware: LED → resistor 220Ω → GPIO4 | Botão → GPIO14 e GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED    4
#define PINO_BOTAO 14

bool ledLigado = false;

void setup() {
  pinMode(PINO_LED,   OUTPUT);
  // INPUT_PULLUP: HIGH = solto, LOW = pressionado (sem resistor externo)
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  digitalWrite(PINO_LED, LOW);
  Serial.begin(115200);
  Serial.println("Pressione o botão para ligar/desligar o LED");
}

void loop() {
  if (digitalRead(PINO_BOTAO) == LOW) {
    delay(50);  // debounce — aguarda o bounce se estabilizar
    if (digitalRead(PINO_BOTAO) == LOW) {
      ledLigado = !ledLigado;  // inverte o estado
      digitalWrite(PINO_LED, ledLigado ? HIGH : LOW);
      Serial.println(ledLigado ? "LED ligado" : "LED desligado");
      while (digitalRead(PINO_BOTAO) == LOW);  // aguarda soltar
      delay(50);  // debounce na soltura
    }
  }
}
