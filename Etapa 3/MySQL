#include <DHT.h> // https://github.com/adafruit/DHT-sensor-library  
#include <DHT_U.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN    2
#define DHTTYPE   DHT11
DHT dht(DHTPIN, DHTTYPE);

float t = 0;

const char* ssid = "nombre red";
const char* password = "password";

HTTPClient httpClient;
WiFiClient wClient;

String URL = "http://IP:Puerto/Temperature";

void setup() {
  Serial.begin(9600); // Inicializar conexión serial
  Serial.println("***Inicializando conexión a My SQL***");
  
  dht.begin(); 
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a red WiFi \"");
  Serial.print(ssid);
  Serial.print("\"");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConectado! IP: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void logIntento(float t){
  if(WiFi.status() == WL_CONNECTED){
    String device = "1";
    String temp;
    temp= String(t);
    String postData;
    postData = "{\"logId\":0, \"logDate\":\"2024-03-23\", \"deviceId\":"+device+",\"temp\":"+temp+"}";
    Serial.print("Post Data String: ");
    Serial.println(postData);
    
    Serial.print("Host: ");
    Serial.println(URL);

    httpClient.begin(wClient, URL);
    httpClient.addHeader("Content-Type", "application/json");

    int httpCode = httpClient.POST(postData);

    Serial.print("Response Code: ");
    Serial.println(httpCode);
 
    httpClient.end();
  }
  return;
}

void loop() {
  if (t != dht.readTemperature()) {
    t = dht.readTemperature();

    if (isnan(t)) {
      Serial.println("Error obteniendo los datos del sensor DHT11");
      return;
    }

    Serial.print("\nTemperatura: ");
    Serial.print(t);
    Serial.print(" ºC\t");
    Serial.println("");
    
    logIntento(t);
      
    delay(10000);
  }  
}
