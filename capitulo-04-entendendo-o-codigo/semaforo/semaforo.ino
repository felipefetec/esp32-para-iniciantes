/*
 * Projeto: Semáforo com 3 LEDs
 * Livro: ESP32 Descomplicado — Capítulo 4
 * Autor: Felipe Tavares
 * Descrição: Simula um semáforo real com LED vermelho, amarelo e verde,
 *            usando variáveis para controlar os tempos de cada fase.
 * Hardware: ESP32 DevKit v1 + 3 LEDs + 3 resistores 220Ω + protoboard
 *           LED vermelho → GPIO4
 *           LED amarelo  → GPIO5
 *           LED verde    → GPIO13
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 * Wokwi: montar conforme descrito no capítulo
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

// Pinos de cada LED — #define para não ocupar memória RAM
#define LED_VERMELHO 4
#define LED_AMARELO  5
#define LED_VERDE    13

// Tempos de cada fase do semáforo em milissegundos.
// Centralizar aqui facilita ajustar sem precisar caçar os valores no código.
#define TEMPO_VERMELHO 5000  // 5 segundos parado
#define TEMPO_AMARELO  2000  // 2 segundos de atenção
#define TEMPO_VERDE    5000  // 5 segundos passando

void setup() {
  // Configura os três pinos como saída
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO,  OUTPUT);
  pinMode(LED_VERDE,    OUTPUT);

  // Garante que todos começam apagados
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    LOW);

  Serial.begin(115200);
  Serial.println("Semáforo iniciado!");
}

void loop() {
  // --- Fase vermelha: sinal fechado ---
  // Acende só o vermelho, apaga os outros
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    LOW);
  Serial.println("VERMELHO — sinal fechado");
  delay(TEMPO_VERMELHO);

  // --- Fase amarela: atenção, vai fechar ---
  // Apaga vermelho, acende amarelo
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  HIGH);
  digitalWrite(LED_VERDE,    LOW);
  Serial.println("AMARELO — atenção");
  delay(TEMPO_AMARELO);

  // --- Fase verde: sinal aberto ---
  // Apaga amarelo, acende verde
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    HIGH);
  Serial.println("VERDE — sinal aberto");
  delay(TEMPO_VERDE);

  // --- Fase amarela novamente: vai fechar ---
  // O semáforo real volta pelo amarelo antes de fechar
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  HIGH);
  digitalWrite(LED_VERDE,    LOW);
  Serial.println("AMARELO — fechando...");
  delay(TEMPO_AMARELO);

  // Após esse delay, o loop reinicia e volta para o vermelho
}
