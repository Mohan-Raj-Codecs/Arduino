#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

//Variables
#define led 19  //Optoisolator Activator

//Prototypes
void Wifi_connect(char*,char*);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Wifi_connect("Mohan's Wifi","mohanraj");
}

void loop() {
  // put your main code here, to run repeatedly:
  if((WiFi.status() == WL_CONNECTED)) //Check connection
  {
    HTTPClient client;
    String payload;
    client.begin("http://switches.zapto.org/api/data");
    int httpCode = client.GET();

    if(httpCode > 0){
      payload = client.getString();
      Serial.println(payload);
    }
    else{
      Serial.println("Error on HTTP Request :(");
      Serial.println("Status Code : "+String(httpCode));
    }
    StaticJsonDocument<32> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.println("No Internet Access :(");
      Serial.print("deserializeJson() failed: ");
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
  Serial.print("Connection Lost :(\nRe-");
  Wifi_connect("Mohan's Wifi","mohanraj");
  delay(5000);
  }
  delay(500);
}

void Wifi_connect(char* ssid,char* password){
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
