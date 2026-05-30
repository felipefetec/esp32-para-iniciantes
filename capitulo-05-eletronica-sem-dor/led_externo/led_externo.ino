/*
 * Projeto: LED externo na protoboard
 * Livro: ESP32 Descomplicado — Capítulo 5
 * Autor: Felipe Tavares
 * Descrição: Pisca um LED externo conectado ao GPIO4 com resistor de 220Ω.
 *            Mesma lógica do Blink, agora com componente externo montado
 *            corretamente na protoboard.
 * Hardware: ESP32 DevKit v1 + 1 LED + 1 resistor 220Ω + protoboard + jumpers
 *           Anodo (+) do LED → resistor 220Ω → GPIO4
 *           Catodo (-) do LED → GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// Usamos GPIO4 para o LED externo — diferente do GPIO2 (LED embutido).
// Isso deixa claro que estamos controlando um componente externo.
#define LED_EXTERNO 4

void setup() {
  // Configura o pino como saída para poder enviar tensão ao LED
  pinMode(LED_EXTERNO, OUTPUT);

  Serial.begin(115200);
  Serial.println("LED externo pronto!");
}

void loop() {
  // Liga o LED externo
  digitalWrite(LED_EXTERNO, HIGH);
  Serial.println("LED ligado");
  delay(1000);

  // Desliga o LED externo
  digitalWrite(LED_EXTERNO, LOW);
  Serial.println("LED desligado");
  delay(1000);
}
