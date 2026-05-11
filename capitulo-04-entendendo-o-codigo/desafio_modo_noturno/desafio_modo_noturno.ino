/*
 * Projeto: Desafio — Semáforo com modo noturno
 * Livro: ESP32 para Iniciantes — Capítulo 4 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Semáforo com variável bool modoNoturno. Quando true, apenas
 *            o LED amarelo pisca a cada 1 segundo (como semáforos de madrugada).
 * Hardware: LED vermelho → GPIO4 | LED amarelo → GPIO5 | LED verde → GPIO13
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define LED_VERMELHO   4
#define LED_AMARELO    5
#define LED_VERDE     13
#define TEMPO_VERMELHO 5000
#define TEMPO_AMARELO  2000
#define TEMPO_VERDE    5000

// Altere para true para ativar o modo noturno e grave novamente
bool modoNoturno = false;

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO,  OUTPUT);
  pinMode(LED_VERDE,    OUTPUT);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    LOW);
  Serial.begin(115200);
  Serial.println(modoNoturno ? "Modo NOTURNO ativado" : "Modo NORMAL ativado");
}

void loop() {
  if (modoNoturno) {
    // Modo noturno: só o amarelo pisca a cada 1 segundo
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE,    LOW);
    digitalWrite(LED_AMARELO, HIGH);
    delay(500);
    digitalWrite(LED_AMARELO, LOW);
    delay(500);
  } else {
    // Modo normal: ciclo completo do semáforo
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO,  LOW);
    digitalWrite(LED_VERDE,    LOW);
    delay(TEMPO_VERMELHO);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO,  HIGH);
    delay(TEMPO_AMARELO);
    digitalWrite(LED_AMARELO,  LOW);
    digitalWrite(LED_VERDE,    HIGH);
    delay(TEMPO_VERDE);
    digitalWrite(LED_VERDE,   LOW);
    digitalWrite(LED_AMARELO, HIGH);
    delay(TEMPO_AMARELO);
    digitalWrite(LED_AMARELO, LOW);
  }
}
