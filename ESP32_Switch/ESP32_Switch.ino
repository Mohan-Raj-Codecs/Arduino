#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#define led 19

const char* ssid = "Mohan's Wifi";
const char* password = "mohanraj";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  WiFi.begin(ssid,password);
  Serial.print("Connecting to Wifi");

  while (WiFi.status() !=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the Wifi :)");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your m ain code here, to run repeatedly:
  if((WiFi.status() == WL_CONNECTED)) //Check connection
  {
    HTTPClient client;
    String payload;
    client.begin("http://switches.zapto.org/api/data");
    int httpCode = client.GET();

    if(httpCode > 0){
      payload = client.getString();
      Serial.println("Status Code : "+String(httpCode));
      Serial.println(payload);
    }
    else{
      Serial.println("Error on HTTP Request :(");
    }
 StaticJsonDocument<32> doc;

 DeserializationError error = deserializeJson(doc, payload);

 if (error) {
   Serial.print(F("deserializeJson() failed: "));
   Serial.println(error.f_str());
   return;
  }

  bool oni = doc["on"];

  if(oni){
    Serial.println("Cool");
    digitalWrite(led,HIGH);
  }
  else{
    Serial.println("Not Cool");
    digitalWrite(led,LOW); 
   }
  }
  else{
  Serial.println("Connection Lost :(");
  delay(5000);
  }
  delay(500);
}
