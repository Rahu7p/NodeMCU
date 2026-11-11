#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

// Configuracion del sensor
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Credenciales
const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";
const char* apiKey = "TU_API_KEY";

// Utiliza un identificador de modelo disponible en Google AI Studio
const char* modelo = "MODELO_DISPONIBLE";

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Conexion Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado");

  delay(2000);

  // Obtener mediciones reales
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer el sensor");
    return;
  }

  Serial.println("\n=== DATOS DEL SENSOR ===");
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Humedad: ");
  Serial.println(humedad);

  // Configurar conexion HTTPS
  WiFiClientSecure client;
  client.setInsecure(); // Solo para pruebas

  HTTPClient https;

  String url =
    "https://generativelanguage.googleapis.com/v1beta/models/";

  url += modelo;
  url += ":generateContent";

  if (!https.begin(client, url)) {
    Serial.println("Error al iniciar HTTPS");
    return;
  }

  https.addHeader("Content-Type", "application/json");
  https.addHeader("x-goog-api-key", apiKey);

  // Construir pregunta con datos del sensor
  String pregunta = "Un sensor DHT11 registra una temperatura de ";

  pregunta += String(temperatura, 1);
  pregunta += " grados Celsius y una humedad relativa de ";
  pregunta += String(humedad, 1);

  pregunta += " por ciento. Interpreta estas mediciones, ";
  pregunta += "explica sus limitaciones y proporciona una ";
  pregunta += "recomendacion breve.";

  // Construir solicitud JSON
  JsonDocument solicitud;

  solicitud["contents"][0]["parts"][0]["text"] = pregunta;

  String cuerpo;
  serializeJson(solicitud, cuerpo);

  // Enviar solicitud
  Serial.println("\nConsultando modelo de IA...");

  int codigo = https.POST(cuerpo);

  Serial.print("Codigo HTTP: ");
  Serial.println(codigo);

  if (codigo == 200) {

    String respuesta = https.getString();

    JsonDocument resultado;

    DeserializationError error =
      deserializeJson(resultado, respuesta);

    if (!error) {

      const char* texto =
        resultado["candidates"][0]["content"]["parts"][0]["text"];

      if (texto != nullptr) {
        Serial.println("\n=== RESPUESTA DEL MODELO ===");
        Serial.println(texto);
      } else {
        Serial.println("No se encontro una respuesta");
      }

    } else {
      Serial.println("Error al interpretar JSON");
    }

  } else {
    Serial.println("Error en la solicitud:");
    Serial.println(https.getString());
  }

  https.end();
}

void loop() {
  // La consulta se realiza una sola vez
}
