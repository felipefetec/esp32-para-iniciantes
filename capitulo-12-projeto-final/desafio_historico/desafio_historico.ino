/*
 * Projeto: Desafio — Estação Climática com histórico de leituras
 * Livro: ESP32 Descomplicado — Capítulo 12 (Desafio 1)
 * Autor: Felipe Tavares
 * Hardware: ESP32 DevKit v1
 *           DHT11 dados → GPIO15 | VCC → 3,3V | GND → GND
 *           LED vermelho → resistor 220Ω → GPIO4 | catodo → GND
 * Bibliotecas: WiFi.h, WebServer.h (inclusas), DHT sensor library by Adafruit
 *
 * Adiciona a rota /historico que exibe as últimas 5 leituras em tabela.
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

#define PINO_DHT  15
#define TIPO_DHT  DHT11
#define PINO_LED  4

#define TEMP_LIMITE 30.0
#define UMID_LIMITE 70.0

// Tamanho do histórico — quantas leituras guardar
#define TAM_HISTORICO 5

DHT dht(PINO_DHT, TIPO_DHT);
WebServer server(80);

float temperatura = 0.0;
float umidade     = 0.0;
bool  alertaAtivo = false;

unsigned long ultimaLeitura = 0;

// Arrays para guardar as últimas TAM_HISTORICO leituras
float histTemp[TAM_HISTORICO] = {0};
float histUmid[TAM_HISTORICO] = {0};
int   totalLeituras = 0;  // quantas leituras foram feitas até agora

void atualizarSensor() {
  if (millis() - ultimaLeitura < 2000) return;
  ultimaLeitura = millis();

  float t = dht.readTemperature();
  float u = dht.readHumidity();

  if (!isnan(t) && !isnan(u)) {
    temperatura = t;
    umidade     = u;

    // Desloca o histórico para a esquerda e insere a nova leitura no final
    // Posição 0 é a mais antiga, posição TAM_HISTORICO-1 é a mais recente
    for (int i = 0; i < TAM_HISTORICO - 1; i++) {
      histTemp[i] = histTemp[i + 1];
      histUmid[i] = histUmid[i + 1];
    }
    histTemp[TAM_HISTORICO - 1] = temperatura;
    histUmid[TAM_HISTORICO - 1] = umidade;

    if (totalLeituras < TAM_HISTORICO) totalLeituras++;
  }

  alertaAtivo = (temperatura > TEMP_LIMITE || umidade > UMID_LIMITE);
  digitalWrite(PINO_LED, alertaAtivo ? HIGH : LOW);
}

void handleRaiz() {
  atualizarSensor();

  String corTemp   = (temperatura > TEMP_LIMITE) ? "#e53935" : "#2e7d32";
  String corUmid   = (umidade     > UMID_LIMITE) ? "#e53935" : "#1565c0";
  String corAlerta = alertaAtivo ? "#e53935" : "#2e7d32";
  String textoAlerta = alertaAtivo ? "ALERTA ATIVO" : "Normal";

  String pagina = "<!DOCTYPE html><html><head>";
  pagina += "<meta charset='UTF-8'>";
  pagina += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  pagina += "<meta http-equiv='refresh' content='10'>";
  pagina += "<title>Estação Climática</title>";
  pagina += "<style>";
  pagina += "body{font-family:sans-serif;text-align:center;margin:0;background:#f5f5f5;}";
  pagina += "h1{background:#1565c0;color:white;padding:20px;margin:0;}";
  pagina += ".card{display:inline-block;background:white;border-radius:12px;";
  pagina += "padding:30px 40px;margin:20px 10px;box-shadow:0 2px 8px rgba(0,0,0,0.15);}";
  pagina += ".valor{font-size:48px;font-weight:bold;margin:10px 0;}";
  pagina += ".label{font-size:16px;color:#666;margin-bottom:5px;}";
  pagina += ".alerta{font-size:22px;font-weight:bold;padding:15px 30px;";
  pagina += "border-radius:8px;margin:10px auto;display:inline-block;color:white;}";
  pagina += ".link{display:inline-block;margin-top:15px;padding:10px 20px;";
  pagina += "background:#1565c0;color:white;text-decoration:none;border-radius:6px;}";
  pagina += ".rodape{color:#999;font-size:13px;margin-top:20px;padding-bottom:20px;}";
  pagina += "</style></head><body>";
  pagina += "<h1>Estação Climática ESP32</h1>";
  pagina += "<div class='card'><div class='label'>Temperatura</div>";
  pagina += "<div class='valor' style='color:" + corTemp + ";'>" + String(temperatura, 1) + " °C</div></div>";
  pagina += "<div class='card'><div class='label'>Umidade</div>";
  pagina += "<div class='valor' style='color:" + corUmid + ";'>" + String(umidade, 1) + " %</div></div>";
  pagina += "<br><div class='alerta' style='background:" + corAlerta + ";'>LED: " + textoAlerta + "</div>";
  pagina += "<br><a class='link' href='/historico'>Ver histórico</a>";
  pagina += "<p class='rodape'>Atualiza automaticamente a cada 10 segundos</p>";
  pagina += "</body></html>";

  server.send(200, "text/html", pagina);
}

void handleHistorico() {
  String pagina = "<!DOCTYPE html><html><head>";
  pagina += "<meta charset='UTF-8'>";
  pagina += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  pagina += "<title>Histórico</title>";
  pagina += "<style>";
  pagina += "body{font-family:sans-serif;text-align:center;margin:0;background:#f5f5f5;}";
  pagina += "h1{background:#1565c0;color:white;padding:20px;margin:0;}";
  pagina += "table{margin:30px auto;background:white;border-radius:10px;";
  pagina += "box-shadow:0 2px 8px rgba(0,0,0,0.15);border-collapse:collapse;min-width:300px;}";
  pagina += "th{background:#1565c0;color:white;padding:12px 20px;}";
  pagina += "td{padding:12px 20px;border-bottom:1px solid #eee;}";
  pagina += ".link{display:inline-block;margin-top:15px;padding:10px 20px;";
  pagina += "background:#1565c0;color:white;text-decoration:none;border-radius:6px;}";
  pagina += "</style></head><body>";
  pagina += "<h1>Histórico de Leituras</h1>";

  if (totalLeituras == 0) {
    pagina += "<p>Nenhuma leitura registrada ainda.</p>";
  } else {
    pagina += "<table><tr><th>#</th><th>Temperatura</th><th>Umidade</th></tr>";

    // Exibe do mais recente para o mais antigo
    for (int i = totalLeituras - 1; i >= 0; i--) {
      int pos = (TAM_HISTORICO - totalLeituras) + i;
      pagina += "<tr><td>" + String(totalLeituras - i) + "</td>";
      pagina += "<td>" + String(histTemp[pos], 1) + " °C</td>";
      pagina += "<td>" + String(histUmid[pos], 1) + " %</td></tr>";
    }
    pagina += "</table>";
  }

  pagina += "<br><a class='link' href='/'>Voltar</a>";
  pagina += "</body></html>";

  server.send(200, "text/html", pagina);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);

  dht.begin();
  delay(1000);

  WiFi.begin(SSID, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  server.on("/",          handleRaiz);
  server.on("/historico", handleHistorico);
  server.begin();

  Serial.print("Acesse: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  atualizarSensor();
  server.handleClient();
}
