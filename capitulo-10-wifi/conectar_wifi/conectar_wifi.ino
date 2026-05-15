/*
 * Projeto: Conectando ao WiFi
 * Livro: ESP32 para Iniciantes — Capítulo 10
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

const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== Conectando ao WiFi ===");
  conectarWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão perdida. Reconectando...");
    conectarWifi();
  }
  Serial.print("IP atual: ");
  Serial.println(WiFi.localIP());
  delay(5000);
}

void conectarWifi() {
  WiFi.begin(SSID, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}
