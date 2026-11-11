#include <ESP8266WiFi.h>       // Permite conectar el NodeMCU a Wi-Fi
#include <WiFiClientSecure.h>  // Permite establecer conexiones HTTPS
#include <ESP8266HTTPClient.h> // Permite enviar solicitudes HTTP
#include <ArduinoJson.h>       // Permite crear y leer datos en formato JSON

// Datos de la red Wi-Fi y clave
const char* ssid = "ssid";
const char* password = "password";
const char* apiKey = "api key";

void setup() {
  Serial.begin(115200); // Inicia la comunicación con la computadora

  // Conectarse a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // Esperar mientras se establece la conexión
  }

  Serial.println("Wi-Fi conectado");

  // Preparar la conexión segura con el servidor de Google
  WiFiClientSecure client;
  client.setInsecure(); // Desactiva la validación del certificado; solo para pruebas

  HTTPClient https;

  // Dirección de la API: incluye el modelo que generará la respuesta
  String url = "https://generativelanguage.googleapis.com/v1beta/models/MODEL_ID:generateContent";

  if (!https.begin(client, url)) {
    Serial.println("Error al iniciar la conexión HTTPS");
    return;
  }

  // Indicar que enviaremos datos JSON y proporcionar la clave API
  https.addHeader("Content-Type", "application/json");
  https.addHeader("x-goog-api-key", apiKey);

  // Construir la pregunta que recibirá Gemini
  JsonDocument request;
  request["contents"][0]["parts"][0]["text"] =
      "Un sensor DHT11 registra una temperatura de [TEMPERATURA] °C y una humedad relativa de [HUMEDAD] %. Interpreta estas mediciones y explica qué conclusiones pueden obtenerse. Indica si las condiciones podrían representar algún riesgo para las personas, qué información adicional necesitarías y cuáles son las limitaciones de utilizar únicamente estos datos. 
Distingue los hechos de las suposiciones y no inventes información que no pueda determinarse a partir de las mediciones.";

  // Convertir el objeto JSON en texto para enviarlo al servidor
  String body;
  serializeJson(request, body);

  // Enviar la pregunta y recibir el código de respuesta HTTP
  int code = https.POST(body);
  Serial.printf("Código HTTP: %d\n", code);

  if (code == 200) { // El servidor procesó la solicitud correctamente
    String response = https.getString(); // Obtener la respuesta completa

    // Interpretar la respuesta recibida en formato JSON
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, response);

    if (!error) {
      // Localizar el texto generado dentro de la estructura JSON
      const char* answer =
          doc["candidates"][0]["content"]["parts"][0]["text"];

      if (answer) {
        Serial.println("Respuesta de Gemini:");
        Serial.println(answer); // Mostrar la respuesta en el monitor serie
      } else {
        Serial.println("No se encontró texto en la respuesta");
      }
    } else {
      Serial.println("Error al interpretar el JSON");
    }
  } else {
    // Si ocurre un error, mostrar el mensaje devuelto por el servidor
    Serial.println(https.getString());
  }

  https.end(); // Cerrar la conexión y liberar recursos
}

void loop() {
  // No se repite ninguna acción: la consulta se realiza una sola vez
}
