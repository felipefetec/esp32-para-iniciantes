/*
 * Projeto: Estação climática no Monitor Serial
 * Livro: ESP32 Descomplicado — Capítulo 9
 * Autor: Felipe Tavares
 * Descrição: Lê temperatura e umidade do sensor DHT11 e exibe os valores
 *            no Monitor Serial a cada 2 segundos.
 * Hardware: ESP32 DevKit v1 + módulo DHT11
 *           DHT11: pino de dados → GPIO15 | VCC → 3,3V | GND → GND
 * Bibliotecas: "DHT sensor library" by Adafruit (instalar via Library Manager)
 *              "Adafruit Unified Sensor" (instalada automaticamente como dependência)
 * Testado em: Arduino IDE 2.x, pacote ESP32 by Espressif Systems 3.x
 * Wokwi: usar componente wokwi-dht22 com tipo DHT22 no código (ver capítulo)
 *
 * Se você usar este projeto em publicações, vídeos ou repositórios,
 * mantenha este cabeçalho com a atribuição ao autor.
 */

#include <DHT.h>

#define PINO_DHT  15     // pino de dados do sensor
#define TIPO_DHT  DHT11  // altere para DHT22 se usar o sensor DHT22

// Cria o objeto do sensor com o pino e o tipo definidos acima
DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  Serial.begin(115200);

  // Inicializa o sensor — obrigatório antes de qualquer leitura
  dht.begin();

  Serial.println("Estação climática iniciada!");
  Serial.println("Aguardando primeira leitura...");
}

void loop() {
  // O DHT11 precisa de pelo menos 1 segundo entre leituras.
  // Usamos 2 segundos para garantir estabilidade.
  delay(2000);

  float temperatura = dht.readTemperature();  // °C por padrão
  float umidade     = dht.readHumidity();     // porcentagem

  // isnan() verifica se o valor é inválido ("Not a Number").
  // Isso acontece quando o sensor não respondeu corretamente —
  // verifique a conexão se ocorrer com frequência.
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro: não foi possível ler o sensor DHT11.");
    Serial.println("Verifique a conexão e aguarde...");
    return;  // pula o restante do loop e tenta novamente
  }

  // Exibe os valores formatados no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C  |  Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
}
