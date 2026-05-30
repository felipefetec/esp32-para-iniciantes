/*
 * Projeto: Botão liga/desliga LED (toggle)
 * Livro: ESP32 Descomplicado — Capítulo 6
 * Autor: Felipe Tavares
 * Descrição: Cada pressão no botão alterna o estado do LED entre ligado
 *            e desligado. Usa pull-up interno do ESP32 e debounce por delay.
 * Hardware: ESP32 DevKit v1 + 1 LED + 1 resistor 220Ω + 1 botão push + protoboard
 *           LED → resistor 220Ω → GPIO4
 *           Botão → GPIO14 e GND (sem resistor externo — usa pull-up interno)
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_LED    4
#define PINO_BOTAO  14

// Variável que guarda o estado atual do LED.
// Começa false (apagado) e alterna a cada pressão do botão.
bool ledLigado = false;

void setup() {
  // LED como saída
  pinMode(PINO_LED, OUTPUT);

  // Botão como entrada com pull-up interno ativado.
  // Com pull-up interno, o pino lê HIGH quando o botão está solto
  // e LOW quando o botão é pressionado (conecta o pino ao GND).
  // Isso elimina a necessidade de um resistor externo no circuito.
  pinMode(PINO_BOTAO, INPUT_PULLUP);

  // Estado inicial: LED apagado
  digitalWrite(PINO_LED, LOW);

  Serial.begin(115200);
  Serial.println("Pressione o botão para ligar/desligar o LED");
}

void loop() {
  // Verifica se o botão foi pressionado.
  // LOW significa pressionado porque o pull-up mantém o pino em HIGH
  // — quando o botão é apertado, ele conecta o pino diretamente ao GND.
  if (digitalRead(PINO_BOTAO) == LOW) {

    // Debounce: aguarda 50ms e confirma que o botão ainda está pressionado.
    // Sem isso, o contato metálico do botão "treme" por alguns milissegundos
    // ao ser pressionado, gerando múltiplas leituras de um único clique.
    delay(50);
    if (digitalRead(PINO_BOTAO) == LOW) {

      // Alterna o estado: se estava true vira false, se estava false vira true
      ledLigado = !ledLigado;

      // Aplica o novo estado ao LED
      digitalWrite(PINO_LED, ledLigado ? HIGH : LOW);

      // Informa pelo Serial
      if (ledLigado) {
        Serial.println("LED ligado");
      } else {
        Serial.println("LED desligado");
      }

      // Aguarda o botão ser solto antes de continuar.
      // Sem isso, enquanto o botão permanecer pressionado o loop roda
      // repetidamente e o LED fica alternando dezenas de vezes por segundo.
      while (digitalRead(PINO_BOTAO) == LOW);

      // Pequeno delay após soltar para evitar leitura do rebote na soltura
      delay(50);
    }
  }
}
