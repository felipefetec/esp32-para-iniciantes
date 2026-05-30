/*
 * Projeto: Desafio — Servidor web com página de status
 * Livro: ESP32 Descomplicado — Capítulo 11 (Desafio 1)
 * Autor: Felipe Tavares
 * Hardware: ESP32 DevKit v1 | LED → GPIO4 com resistor 220Ω → GND
 * Biblioteca: WiFi.h e WebServer.h (inclusas no pacote ESP32 da Arduino IDE)
 *
 * Além dos botões ligar/desligar, adiciona a rota /status que exibe
 * o estado atual do LED e um botão de toggle (inverte o estado).
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <WiFi.h>
#include <WebServer.h>

const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

#define PINO_LED 4

WebServer server(80);

bool ledLigado = false;

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
    .status   { background-color: #1976D2; }
  </style>
</head>
<body>
  <h1>Controle de LED</h1>
  <a href="/ligar"   ><div class="btn ligar"   >Ligar LED</div></a>
  <a href="/desligar"><div class="btn desligar">Desligar LED</div></a>
  <br>
  <a href="/status"  ><div class="btn status"  >Ver status</div></a>
</body>
</html>
)rawliteral";

void handleRaiz() {
  server.send(200, "text/html", paginaHTML);
}

void handleLigar() {
  digitalWrite(PINO_LED, HIGH);
  ledLigado = true;
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void handleDesligar() {
  digitalWrite(PINO_LED, LOW);
  ledLigado = false;
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

// Página de status: mostra o estado atual e botão de toggle
void handleStatus() {
  // Monta a página dinamicamente com o estado real do LED
  String estado = ledLigado ? "LIGADO" : "DESLIGADO";
  String corEstado = ledLigado ? "#4CAF50" : "#e53935";
  String rotaToggle = ledLigado ? "/desligar" : "/ligar";
  String textoToggle = ledLigado ? "Desligar LED" : "Ligar LED";

  // Concatena o HTML com o estado atual — o valor muda a cada requisição
  String pagina = "<!DOCTYPE html><html><head>";
  pagina += "<meta charset='UTF-8'>";
  pagina += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  pagina += "<title>Status do LED</title>";
  pagina += "<style>body{font-family:sans-serif;text-align:center;margin-top:60px;background:#f0f0f0;}";
  pagina += "h1{color:#333;}.btn{display:inline-block;padding:20px 40px;font-size:20px;";
  pagina += "margin:10px;border:none;border-radius:10px;cursor:pointer;text-decoration:none;color:white;}";
  pagina += ".toggle{background-color:#FF9800;}.voltar{background-color:#607D8B;}</style></head><body>";
  pagina += "<h1>Status do LED</h1>";
  pagina += "<p style='font-size:24px;color:" + corEstado + ";font-weight:bold;'>LED: " + estado + "</p>";
  pagina += "<a href='" + rotaToggle + "'><div class='btn toggle'>" + textoToggle + "</div></a><br>";
  pagina += "<a href='/'><div class='btn voltar'>Voltar</div></a>";
  pagina += "</body></html>";

  server.send(200, "text/html", pagina);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);

  delay(1000);

  WiFi.begin(SSID, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  server.on("/",         handleRaiz);
  server.on("/ligar",    handleLigar);
  server.on("/desligar", handleDesligar);
  server.on("/status",   handleStatus);  // rota extra do desafio

  server.begin();

  Serial.print("Acesse: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
