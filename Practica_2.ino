#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Gudiño"; 
const char* password = "01123581321";
String scriptURL = "https://script.google.com/macros/s/AKfycby1Pz61vBcSIw53sbi80Yv_PhySWLID42-zBT2bZYVbXTQZIBrJn-URJqlEPvcdbPM/exec";
void setup() 
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConectado a WiFi");
}

void loop() 
{
    if (WiFi.status() == WL_CONNECTED) 
    {
      HTTPClient http;
      String iddevice = "ESP32-01";
      float temp = random(20, 30); 
      float humidity = random(40, 60); 
      float gas = random(100, 300);    
      float pressure = random(900, 1100);
      String url = scriptURL + "?iddevice=" + iddevice +
                    "&temp=" + String(temp) + 
                    "&humidity=" + String(humidity) +
                    "&gas=" + String(gas) +
                    "&pressure=" + String(pressure);
      Serial.println("Enviando datos a Google Sheets...");
      Serial.println(url);
      http.begin(url); 
      int httpResponseCode = http.GET(); 
      if (httpResponseCode > 0) 
      {
        String response = http.getString();
        Serial.println("Respuesta del servidor: " + response);
      } 
      else
      {
        Serial.print("Error en la solicitud: ");
        Serial.println(httpResponseCode);
      }
      http.end(); 
    } 
    else 
    {
      Serial.println("WiFi desconectado, reconectando...");
      WiFi.begin(ssid, password);
    }
    delay(60000);
}