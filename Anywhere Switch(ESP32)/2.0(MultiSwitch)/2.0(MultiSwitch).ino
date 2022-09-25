#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>


//Config Variables
int led0 = 18;
int led1 = 19;
int led2 = 21;                                  //Optoisolator Activator
char password[] = "18raj1990";                   //Wifi Password
char ssid_name[] = "Mohan";              //Wifi Name
char url[] = "http://localhost/data.json"; //URL to fetch
float waiter = 1;                               //Fetch Delay in Seconds

//Discrete vars
bool on0 = false;
bool on1 = false;
bool on2 = false;
StaticJsonDocument < 96 > doc; //Refer https://arduinojson.org/v6/assistant/

//Prototypes
void Wifi_connect(char * , char * );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Wifi_connect(ssid_name, password);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((WiFi.status() == WL_CONNECTED)) //Check connection
  {
    HTTPClient client;
    String payload;
    client.begin(url);
    int httpCode = client.GET();

    if (httpCode > 0) {
      payload = client.getString();
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP Request :(");
      Serial.println("Status Code : " + String(httpCode));
    }
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.println("No Internet Access :(");
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }
    on0 = doc["on0"];
    on1 = doc["on1"];
    on2 = doc["on2"];
    update_led();
    delay(500);
  } else {
    Serial.print("Connection Lost :(\nRe-");
    Wifi_connect(ssid_name, password);
    delay(5000);
  }
}

void Wifi_connect(char * ssid, char * password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wifi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(waiter * 1000);
  }

  Serial.println("\nConnected to the Wifi :)");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}

void update_led() {
  digitalWrite(led0, (on0) ? HIGH : LOW);
  digitalWrite(led1, (on1) ? HIGH : LOW);
  digitalWrite(led2, (on2) ? HIGH : LOW);
}
