/*
 * Projeto: Estação Climática WiFi — Projeto Final
 * Livro: ESP32 Descomplicado — Capítulo 12
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

// Credenciais WiFi — substitua pelos dados da sua rede
const char* SSID  = "NomeDaSuaRede";
const char* SENHA = "SenhaDaSuaRede";

// Pinos
#define PINO_DHT  15
#define TIPO_DHT  DHT11
#define PINO_LED  4

// Limites para ativar o alerta
#define TEMP_LIMITE 30.0   // °C — acima disso o LED acende
#define UMID_LIMITE 70.0   // %  — acima disso o LED também acende

DHT dht(PINO_DHT, TIPO_DHT);
WebServer server(80);

// Valores globais — atualizados a cada leitura do sensor
float temperatura  = 0.0;
float umidade      = 0.0;
bool  alertaAtivo  = false;

// Controle de tempo entre leituras do DHT11
// O DHT11 precisa de pelo menos 1s entre leituras — respeitamos 2s
unsigned long ultimaLeitura = 0;

// Lê o sensor e atualiza as variáveis globais
// Só realiza a leitura se passaram pelo menos 2 segundos desde a última
void atualizarSensor() {
  if (millis() - ultimaLeitura < 2000) return;
  ultimaLeitura = millis();

  float t = dht.readTemperature();
  float u = dht.readHumidity();

  // Só atualiza se a leitura for válida — mantém o último valor bom caso falhe
  if (!isnan(t) && !isnan(u)) {
    temperatura = t;
    umidade     = u;
  }

  // Verifica se algum limite foi ultrapassado e aciona o LED
  alertaAtivo = (temperatura > TEMP_LIMITE || umidade > UMID_LIMITE);
  digitalWrite(PINO_LED, alertaAtivo ? HIGH : LOW);
}

// Monta e envia a página principal com os dados atuais
void handleRaiz() {
  atualizarSensor();

  // Cores dinâmicas baseadas nos valores lidos
  String corTemp  = (temperatura > TEMP_LIMITE) ? "#e53935" : "#2e7d32";
  String corUmid  = (umidade     > UMID_LIMITE) ? "#e53935" : "#1565c0";
  String corAlerta = alertaAtivo ? "#e53935" : "#2e7d32";
  String textoAlerta = alertaAtivo ? "ALERTA ATIVO" : "Normal";

  String pagina = "<!DOCTYPE html><html><head>";
  pagina += "<meta charset='UTF-8'>";
  pagina += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  // Atualiza a página automaticamente a cada 10 segundos
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
  pagina += ".rodape{color:#999;font-size:13px;margin-top:20px;padding-bottom:20px;}";
  pagina += "</style></head><body>";
  pagina += "<h1>Estação Climática ESP32</h1>";
  pagina += "<div class='card'>";
  pagina += "<div class='label'>Temperatura</div>";
  pagina += "<div class='valor' style='color:" + corTemp + ";'>" + String(temperatura, 1) + " °C</div>";
  pagina += "</div>";
  pagina += "<div class='card'>";
  pagina += "<div class='label'>Umidade</div>";
  pagina += "<div class='valor' style='color:" + corUmid + ";'>" + String(umidade, 1) + " %</div>";
  pagina += "</div>";
  pagina += "<br><div class='alerta' style='background:" + corAlerta + ";'>LED: " + textoAlerta + "</div>";
  pagina += "<p class='rodape'>Atualiza automaticamente a cada 10 segundos</p>";
  pagina += "</body></html>";

  server.send(200, "text/html", pagina);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);

  dht.begin();
  delay(1000);

  Serial.println("=== Estação Climática WiFi ===");

  // Conecta ao WiFi
  WiFi.begin(SSID, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado!");

  // Registra a rota e inicia o servidor
  server.on("/", handleRaiz);
  server.begin();

  Serial.print("Acesse: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Atualiza o sensor e o LED continuamente, independente do navegador
  atualizarSensor();

  // Verifica e responde às requisições do navegador
  server.handleClient();
}
