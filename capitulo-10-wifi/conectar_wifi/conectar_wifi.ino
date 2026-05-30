/*
 * Projeto: Conectando ao WiFi
 * Livro: ESP32 Descomplicado — Capítulo 10
 * Autor: Felipe Tavares
 * Hardware: ESP32 DevKit v1 — sem componentes extras, só o cabo USB
 * Biblioteca: WiFi.h (já inclusa no pacote ESP32 da Arduino IDE)
 *
 * O ESP32 se conecta à rede WiFi configurada e exibe o endereço IP
 * no Monitor Serial. A cada tentativa de conexão uma mensagem é exibida.
 * Se perder conexão, reconecta automaticamente no próximo loop.
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <WiFi.h>

// Coloque aqui o nome e a senha da sua rede WiFi
// Use aspas duplas — WiFi não aceita aspas simples
const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

void setup() {
  Serial.begin(115200);

  // Pequena pausa para o Monitor Serial abrir antes das primeiras mensagens
  delay(1000);

  Serial.println("=== Conectando ao WiFi ===");
  conectarWifi();
}

void loop() {
  // Verifica se ainda está conectado — se não estiver, reconecta
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão perdida. Reconectando...");
    conectarWifi();
  }

  // Exibe o IP a cada 5 segundos enquanto estiver conectado
  Serial.print("IP atual: ");
  Serial.println(WiFi.localIP());
  delay(5000);
}

// Função responsável por tentar a conexão com a rede WiFi
// Fica em loop até conseguir — o ESP32 não avança sem WiFi neste projeto
void conectarWifi() {
  // Inicia o processo de conexão com a rede informada
  WiFi.begin(SSID, SENHA);

  Serial.print("Conectando");

  // Aguarda até o status mudar para WL_CONNECTED
  // Cada ponto no Monitor Serial = uma tentativa de 500ms
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Chegou aqui: conexão bem-sucedida
  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}
