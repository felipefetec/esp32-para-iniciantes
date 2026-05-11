/*
 * Projeto: LED externo na protoboard
 * Livro: ESP32 para Iniciantes — Capítulo 5
 * Autor: Felipe Tavares
 * Descrição: Pisca um LED externo conectado ao GPIO4 com resistor de 220Ω.
 *            Mesma lógica do Blink, agora com componente externo na protoboard.
 * Hardware: Anodo (+) do LED → resistor 220Ω → GPIO4 | Catodo (-) → GND
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// GPIO4 para o LED externo — diferente do GPIO2 (LED embutido)
#define LED_EXTERNO 4

void setup() {
  pinMode(LED_EXTERNO, OUTPUT);
  Serial.begin(115200);
  Serial.println("LED externo pronto!");
}

void loop() {
  digitalWrite(LED_EXTERNO, HIGH);
  Serial.println("LED ligado");
  delay(1000);
  digitalWrite(LED_EXTERNO, LOW);
  Serial.println("LED desligado");
  delay(1000);
}
