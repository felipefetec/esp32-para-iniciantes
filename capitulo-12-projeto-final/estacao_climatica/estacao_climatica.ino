/*
 * Projeto: Estação Climática WiFi — Projeto Final
 * Livro: ESP32 para Iniciantes — Capítulo 12
 * Autor: Felipe Tavares
 * Hardware: ESP32 DevKit v1
 *           DHT11 dados → GPIO15 | VCC → 3,3V | GND → GND
 *           LED vermelho → resistor 220Ω → GPIO4 | catodo → GND
 * Bibliotecas: WiFi.h e WebServer.h (inclusas no pacote ESP32)
 *              DHT sensor library by Adafruit (instalar via Library Manager)
 *
 * Serve uma página web com temperatura, umidade e status do LED de alerta.
 * O LED acende automaticamente se temperatura > 30°C ou umidade > 70%.
 * A página atualiza a cada 10 segundos automaticamente.
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

#define PINO_DHT    15
#define TIPO_DHT    DHT11
#define PINO_LED    4
#define TEMP_LIMITE 30.0
#define UMID_LIMITE 70.0

DHT dht(PINO_DHT, TIPO_DHT);
WebServer server(80);

float temperatura = 0.0;
float umidade     = 0.0;
bool  alertaAtivo = false;
unsigned long ultimaLeitura = 0;

void atualizarSensor() {
  if (millis() - ultimaLeitura < 2000) return;
  ultimaLeitura = millis();
  float t = dht.readTemperature();
  float u = dht.readHumidity();
  if (!isnan(t) && !isnan(u)) { temperatura = t; umidade = u; }
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
  pagina += "<style>body{font-family:sans-serif;text-align:center;margin:0;background:#f5f5f5;}";
  pagina += "h1{background:#1565c0;color:white;padding:20px;margin:0;}";
  pagina += ".card{display:inline-block;background:white;border-radius:12px;padding:30px 40px;margin:20px 10px;box-shadow:0 2px 8px rgba(0,0,0,0.15);}";
  pagina += ".valor{font-size:48px;font-weight:bold;margin:10px 0;}.label{font-size:16px;color:#666;margin-bottom:5px;}";
  pagina += ".alerta{font-size:22px;font-weight:bold;padding:15px 30px;border-radius:8px;margin:10px auto;display:inline-block;color:white;}";
  pagina += ".rodape{color:#999;font-size:13px;margin-top:20px;padding-bottom:20px;}</style></head><body>";
  pagina += "<h1>Estação Climática ESP32</h1>";
  pagina += "<div class='card'><div class='label'>Temperatura</div>";
  pagina += "<div class='valor' style='color:" + corTemp + ";'>" + String(temperatura, 1) + " °C</div></div>";
  pagina += "<div class='card'><div class='label'>Umidade</div>";
  pagina += "<div class='valor' style='color:" + corUmid + ";'>" + String(umidade, 1) + " %</div></div>";
  pagina += "<br><div class='alerta' style='background:" + corAlerta + ";'>LED: " + textoAlerta + "</div>";
  pagina += "<p class='rodape'>Atualiza automaticamente a cada 10 segundos</p></body></html>";
  server.send(200, "text/html", pagina);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
  dht.begin();
  delay(1000);
  Serial.println("=== Estação Climática WiFi ===");
  WiFi.begin(SSID, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println();
  Serial.println("WiFi conectado!");
  server.on("/", handleRaiz);
  server.begin();
  Serial.print("Acesse: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  atualizarSensor();
  server.handleClient();
}
