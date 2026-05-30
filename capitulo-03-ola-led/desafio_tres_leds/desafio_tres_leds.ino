/*
 * Projeto: Desafio — Três LEDs em sequência (efeito dominó)
 * Livro: ESP32 Descomplicado — Capítulo 3 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Acende e apaga três LEDs externos um após o outro,
 *            criando um efeito de onda contínua.
 * Hardware: ESP32 DevKit v1 + 3 LEDs + 3 resistores de 220Ω + protoboard
 *           LED 1 → GPIO4 | LED 2 → GPIO5 | LED 3 → GPIO13
 *           Cada LED conectado com resistor de 220Ω entre o pino e o anodo (+)
 *           Catodo (-) de cada LED conectado ao GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// Pinos dos três LEDs externos definidos com #define.
// #define não aloca memória RAM — o compilador substitui o nome pelo número
// antes de compilar. Prefira sempre #define para constantes em embarcados.
// GPIO4, GPIO5 e GPIO13 funcionam nos dois modelos de DevKit v1 (38 e 30 pinos).
#define LED1 4
#define LED2 5
#define LED3 13

// Tempo que cada LED fica aceso antes de passar para o próximo (em milissegundos).
// Centralizar aqui facilita ajustar a velocidade da animação sem tocar no loop.
#define TEMPO_ACESO 300

void setup() {
  // Configura os três pinos como saída.
  // Todo pino que vai acionar um componente precisa ser declarado como OUTPUT.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Garante que todos os LEDs começam apagados.
  // Sem isso, o estado inicial dos pinos pode variar e algum LED pode
  // acender sozinho antes da sequência começar.
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() {
  // Acende o LED 1, aguarda, apaga
  digitalWrite(LED1, HIGH);
  delay(TEMPO_ACESO);
  digitalWrite(LED1, LOW);

  // Acende o LED 2, aguarda, apaga
  digitalWrite(LED2, HIGH);
  delay(TEMPO_ACESO);
  digitalWrite(LED2, LOW);

  // Acende o LED 3, aguarda, apaga
  digitalWrite(LED3, HIGH);
  delay(TEMPO_ACESO);
  digitalWrite(LED3, LOW);

  // Pequena pausa antes de reiniciar a sequência.
  // Sem ela a animação parece que nunca "volta ao início" — fica contínua demais.
  delay(150);
}
