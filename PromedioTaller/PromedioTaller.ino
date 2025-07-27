#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

#define DHTTYPE DHT11

// Pines de sensores DHT
#define DHTPIN1 23
#define DHTPIN2 19
#define DHTPIN3 16

// Pines de los LEDs
#define LED1 25
#define LED2 26
#define LED3 27

const char* ssid = "SAA";
const char* password = "SAA135.!!.531AAS";
const char* host = "taller.micursodeciencias.com";
const int httpsPort = 443;

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  // Inicializar sensores
  dht1.begin();
  dht2.begin();
  dht3.begin();

  // Inicializar LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Conectar WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");

  client.setInsecure(); // Omitir verificación SSL
}

void loop() {
    // Encender LEDs
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED3, HIGH);
  delay(1000);
  // Leer sensores
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();
  float t3 = dht3.readTemperature();
  float h3 = dht3.readHumidity();

  // Validar lecturas
  if (isnan(t1) || isnan(h1) || isnan(t2) || isnan(h2) || isnan(t3) || isnan(h3)) {
    Serial.println("❌ Error leyendo uno de los sensores");
    return;
  }

  // Calcular promedios
  float avgTemp = (t1 + t2 + t3) / 3;
  float avgHum = (h1 + h2 + h3) / 3;

  Serial.println("✅ Promedios calculados:");
  Serial.println("Temperatura: " + String(avgTemp));
  Serial.println("Humedad: " + String(avgHum));



  // Construir URL
  String url = "/test_data2.php?temperature=" + String(avgTemp) + "&humidity=" + String(avgHum);
  Serial.println("🔗 URL construida: " + url);

  // Conexión HTTPS
  Serial.println("🌐 Conectando al servidor...");
  if (!client.connect(host, httpsPort)) {
    Serial.println("❌ Conexión HTTPS fallida");
    return;
  }

  // Enviar GET
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP32\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String respuesta = client.readString();
  Serial.println("📩 Respuesta del servidor:");
  Serial.println(respuesta);

  delay(1000);
}