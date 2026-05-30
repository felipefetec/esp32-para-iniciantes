/*
 * Projeto: Desafio — Barra de progresso no Monitor Serial
 * Livro: ESP32 Descomplicado — Capítulo 8 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Lê o potenciômetro e exibe uma barra de progresso visual
 *            no Monitor Serial proporcional ao valor lido, junto com
 *            a porcentagem e o valor bruto do ADC.
 *            Exemplo de saída: [#####.....] 50% (ADC: 2047)
 * Hardware: ESP32 DevKit v1 + potenciômetro 10kΩ + LED + resistor 220Ω
 *           Potenciômetro SIG → GPIO32 | LED → GPIO4
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define PINO_POT  32
#define PINO_LED   4
#define LARGURA   20   // número de caracteres da barra

// Exibe a barra de progresso no Monitor Serial.
// valor: leitura atual (0–4095) | maximo: valor máximo da faixa
void mostrarBarra(int valor, int maximo) {
  // Calcula a porcentagem atual
  int porcentagem = map(valor, 0, maximo, 0, 100);

  // Quantos blocos da barra ficam preenchidos
  int preenchido = map(valor, 0, maximo, 0, LARGURA);

  // Monta a barra caractere por caractere
  Serial.print("[");
  for (int i = 0; i < LARGURA; i++) {
    if (i < preenchido) {
      Serial.print("#");   // bloco preenchido
    } else {
      Serial.print(".");   // bloco vazio
    }
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

  // Controla o brilho do LED ao mesmo tempo que exibe a barra
  analogWrite(PINO_LED, brilho);

  // Exibe a barra proporcional ao valor lido
  mostrarBarra(leitura, 4095);

  delay(150);
}
