/*
 * Projeto: Desafio — Semáforo com modo noturno
 * Livro: ESP32 Descomplicado — Capítulo 4 (Desafio)
 * Autor: Felipe Tavares
 * Descrição: Semáforo normal que pode ser colocado em modo noturno
 *            alterando uma variável bool. No modo noturno só o LED amarelo
 *            pisca a cada 1 segundo, como nos semáforos de madrugada.
 * Hardware: ESP32 DevKit v1 + 3 LEDs + 3 resistores 220Ω + protoboard
 *           LED vermelho → GPIO4 | LED amarelo → GPIO5 | LED verde → GPIO13
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#define LED_VERMELHO 4
#define LED_AMARELO  5
#define LED_VERDE    13

#define TEMPO_VERMELHO 5000
#define TEMPO_AMARELO  2000
#define TEMPO_VERDE    5000

// Variável bool que controla o modo de operação.
// true  = modo noturno (só amarelo piscando)
// false = modo normal  (semáforo completo)
// Para ativar o modo noturno, basta trocar false por true aqui e regravar.
bool modoNoturno = false;

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO,  OUTPUT);
  pinMode(LED_VERDE,    OUTPUT);

  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO,  LOW);
  digitalWrite(LED_VERDE,    LOW);

  Serial.begin(115200);

  // Avisa no Serial qual modo está ativo ao ligar
  if (modoNoturno) {
    Serial.println("Modo NOTURNO ativado — amarelo piscando");
  } else {
    Serial.println("Modo NORMAL ativado — semáforo completo");
  }
}

void loop() {
  // O if verifica o valor da variável a cada ciclo do loop.
  // Dependendo do valor, executa um comportamento diferente.
  if (modoNoturno) {
    // Modo noturno: apaga vermelho e verde, pisca só o amarelo
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE,    LOW);

    digitalWrite(LED_AMARELO, HIGH);
    delay(500);   // meio segundo aceso
    digitalWrite(LED_AMARELO, LOW);
    delay(500);   // meio segundo apagado
    // Total: 1 piscada por segundo

  } else {
    // Modo normal: ciclo completo do semáforo

    // Vermelho
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO,  LOW);
    digitalWrite(LED_VERDE,    LOW);
    delay(TEMPO_VERMELHO);

    // Amarelo (vai abrir)
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO,  HIGH);
    delay(TEMPO_AMARELO);

    // Verde
    digitalWrite(LED_AMARELO,  LOW);
    digitalWrite(LED_VERDE,    HIGH);
    delay(TEMPO_VERDE);

    // Amarelo (vai fechar)
    digitalWrite(LED_VERDE,   LOW);
    digitalWrite(LED_AMARELO, HIGH);
    delay(TEMPO_AMARELO);

    // Apaga amarelo antes do loop reiniciar no vermelho
    digitalWrite(LED_AMARELO, LOW);
  }
}
