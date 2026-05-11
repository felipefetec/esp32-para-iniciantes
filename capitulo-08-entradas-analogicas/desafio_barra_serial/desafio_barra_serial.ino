/*
 * Projeto: Desafio — Barra de progresso no Monitor Serial
 * Livro: ESP32 para Iniciantes — Capítulo 8 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Exibe barra de progresso visual proporcional ao valor do ADC.
 *            Exemplo: [#####.....] 50% (ADC: 2047)
 * Hardware: Potenciômetro SIG → GPIO32 | LED → GPIO4
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_POT  32
#define PINO_LED   4
#define LARGURA   20

void mostrarBarra(int valor, int maximo) {
  int porcentagem = map(valor, 0, maximo, 0, 100);
  int preenchido  = map(valor, 0, maximo, 0, LARGURA);

  Serial.print("[");
  for (int i = 0; i < LARGURA; i++) {
    Serial.print(i < preenchido ? "#" : ".");
  }
  Serial.print("] ");
  Serial.print(porcentagem);
  Serial.print("% (ADC: ");
  Serial.print(valor);
  Serial.println(")");
}

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Gire o potenciômetro e acompanhe a barra:");
}

void loop() {
  int leitura = analogRead(PINO_POT);
  int brilho  = map(leitura, 0, 4095, 0, 255);
  analogWrite(PINO_LED, brilho);
  mostrarBarra(leitura, 4095);
  delay(150);
}
