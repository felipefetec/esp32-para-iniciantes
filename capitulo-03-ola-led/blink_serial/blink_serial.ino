/*
 * Projeto: Blink com Monitor Serial
 * Livro: ESP32 Descomplicado — Capítulo 3
 * Autor: Felipe Tavares
 * Descrição: Pisca o LED embutido e envia mensagens pelo Monitor Serial,
 *            mostrando o estado atual do LED a cada mudança.
 * Hardware: ESP32 DevKit v1 (38 ou 30 pinos) — só o cabo USB, sem componentes extras
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montagem não necessária — usa apenas o LED embutido da placa
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// Pino do LED embutido no ESP32 DevKit v1.
// Usamos #define em vez de "int PINO_LED = 2" porque #define não ocupa
// memória RAM — o compilador substitui o nome pelo valor antes de compilar.
// Para constantes em microcontroladores, sempre prefira #define.
#define PINO_LED 2

void setup() {
  // Inicia a comunicação serial a 115200 baud.
  // Esse valor precisa ser o mesmo configurado no Monitor Serial da IDE,
  // senão o texto vai aparecer como caracteres estranhos na tela.
  Serial.begin(115200);

  // Configura o pino do LED como saída.
  // Sem isso, o pino fica em estado indefinido e o LED pode se comportar
  // de forma imprevisível.
  pinMode(PINO_LED, OUTPUT);

  // Mensagem inicial para confirmar que o ESP32 inicializou corretamente.
  // Aparece uma vez quando a placa liga ou é reiniciada.
  Serial.println("ESP32 iniciado! Começando o blink...");
}

void loop() {
  // Liga o LED e avisa pelo Serial
  digitalWrite(PINO_LED, HIGH);
  Serial.println("LED ligado");

  // Aguarda 1 segundo com o LED aceso
  delay(1000);

  // Desliga o LED e avisa pelo Serial
  digitalWrite(PINO_LED, LOW);
  Serial.println("LED desligado");

  // Aguarda 1 segundo com o LED apagado
  delay(1000);
}
