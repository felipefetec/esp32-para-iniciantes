/*
 * Projeto: ESP32 como servidor web — controle de LED pelo celular
 * Livro: ESP32 Descomplicado — Capítulo 11
 * Autor: Felipe Tavares
 * Hardware: ESP32 DevKit v1 | LED → GPIO4 com resistor 220Ω → GND
 * Biblioteca: WiFi.h e WebServer.h (inclusas no pacote ESP32 da Arduino IDE)
 *
 * O ESP32 serve uma página HTML simples acessível por qualquer dispositivo
 * na mesma rede WiFi. A página exibe dois botões: ligar e desligar o LED.
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <WiFi.h>
#include <WebServer.h>

const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

#define PINO_LED 4

// Cria o servidor na porta 80 — a porta padrão do protocolo HTTP
WebServer server(80);

// Estado atual do LED — precisamos guardar para mostrar na página
bool ledLigado = false;

// Página HTML enviada ao navegador quando alguém acessa o IP do ESP32
// R"rawliteral(...)rawliteral" é uma string literal crua — sem necessidade de escapar aspas
const char* paginaHTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 - LED</title>
  <style>
    body { font-family: sans-serif; text-align: center; margin-top: 60px; background: #f0f0f0; }
    h1 { color: #333; }
    .btn { display: inline-block; padding: 20px 40px; font-size: 20px;
           margin: 10px; border: none; border-radius: 10px; cursor: pointer;
           text-decoration: none; color: white; }
    .ligar    { background-color: #4CAF50; }
    .desligar { background-color: #e53935; }
  </style>
</head>
<body>
  <h1>Controle de LED</h1>
  <p>ESP32 Servidor Web</p>
  <a href="/ligar"   ><div class="btn ligar"   >Ligar LED</div></a>
  <a href="/desligar"><div class="btn desligar">Desligar LED</div></a>
</body>
</html>
)rawliteral";

// Envia a página principal ao navegador
void handleRaiz() {
  server.send(200, "text/html", paginaHTML);
}

// Liga o LED e redireciona de volta para a página principal
void handleLigar() {
  digitalWrite(PINO_LED, HIGH);
  ledLigado = true;
  // Redireciona para a raiz — assim o navegador volta para a página de controle
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

// Desliga o LED e redireciona de volta para a página principal
void handleDesligar() {
  digitalWrite(PINO_LED, LOW);
  ledLigado = false;
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);

  delay(1000);
  Serial.println("=== ESP32 Servidor Web ===");

  // Conecta ao WiFi
  WiFi.begin(SSID, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado!");

  // Registra as rotas — cada URL chama uma função específica
  server.on("/",         handleRaiz);
  server.on("/ligar",    handleLigar);
  server.on("/desligar", handleDesligar);

  // Inicia o servidor HTTP
  server.begin();

  // Exibe o IP — é com esse endereço que você vai acessar do celular
  Serial.print("Acesse no navegador: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // handleClient() verifica se algum navegador fez uma requisição
  // e chama a função correspondente à rota acessada
  server.handleClient();
}
