#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>


const char* ssid = "Galaxy A11cbb6";
const char* password = "ijov8519";


const int LED_VERDE = 18;
const int LED_VERMELHO = 19;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_VERDE, LOW);

  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado com sucesso!");
}

void loop() {
 
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
    Serial.println("Wi-Fi desconectado! Tentando reconectar...");
    WiFi.begin(ssid, password);
  } 
  else {
  
    WiFiClientSecure *client = new WiFiClientSecure;
    if (client) {
      client->setSecure(); 
      
      HTTPClient http;
      Serial.print("[HTTP] Iniciando requisição...\n");
      
     
      http.begin(*client, "https://jsonplaceholder.typicode.com/todos/1"); 

      int httpCode = http.GET();

      if (httpCode == 200) {
        Serial.printf("[HTTP] Sucesso: %d\n", httpCode);
        digitalWrite(LED_VERDE, HIGH);
        digitalWrite(LED_VERMELHO, LOW);
      } else {
        Serial.printf("[HTTP] Falha ou Erro: %d\n", httpCode);
        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_VERMELHO, HIGH);
      }

      http.end(); 
      delete client; 
    }
  }

  Serial.println("Aguardando 15 segundos para a próxima checagem...");
  delay(15000); 
}