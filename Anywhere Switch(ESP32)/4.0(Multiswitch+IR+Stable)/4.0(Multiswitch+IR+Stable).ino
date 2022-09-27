#include <IRremote.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define MARK_EXCESS_MICROS    20 // recommended for the cheap modules for memory protect


//Config Variables
int IR_RECEIVE_PIN = 15; //Remote
HTTPClient client;
String payload;

int led0 = 13;
int led1 = 12;
int led2 = 14;                                  
int led3 = 27;                                  //Optoisolator Activator
char password[] = "mohanraj";                   //Wifi Password
char ssid_name[] = "Redmi Note 4";              //Wifi Name
char url[] = "http://localhost:81/api/data";       //URL to fetch
float waiter = 1;                               //Fetch Delay in Seconds
int internet_access = 0;

//Discrete vars
int ir_code = 0, last_ms = millis(); //Remote

bool on0 = false;
bool on1 = false;
bool on2 = false;
bool on3 = false;
StaticJsonDocument < 96 > doc; //Refer https://arduinojson.org/v6/assistant/

//Prototypes
void Wifi_connect(char * , char * );
bool inv(bool x);
int req(String url);
void Handle_ir_code(int ir_code);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Wifi_connect(ssid_name, password);
  Serial.print(F("Ready to receive json packets :)"));

  #if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
  delay(2000); // To be able to connect Serial monitor after reset or power up and before first printout
  #endif
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);

}



void loop() {
  //IR_Code_Functions here
  if (IrReceiver.decode()) {  // Grab an IR code
    if(isRepeat(IrReceiver.decodedIRData.decodedRawData)){
      ir_code = IrReceiver.decodedIRData.decodedRawData;
      goto res;
    }
    ir_code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(ir_code);
    Handle_ir_code(ir_code);
    update_led();
    res:;
    IrReceiver.resume();                            // Prepare for the next value
  }
  
  //Internet Stuffs here
  if ((WiFi.status() == WL_CONNECTED)) //Check connection
  {
    //HTTPClient client;
    //String payload;
    client.begin(url);
    int httpCode = client.GET();

    if (httpCode > 0) {
      payload = client.getString();
      internet_access = 1;
     // Serial.println(payload);
    } else {
      Serial.println("Error on HTTP Request :(");
      Serial.println("Status Code : " + String(httpCode));
      internet_access = 0;
    }
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.println("No Internet Access :( or Check your algorithm array size declarations");
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      internet_access = 0;
      return;
    }
    on0 = doc["on0"];
    on1 = doc["on1"];
    on2 = doc["on2"];
    on3 = doc["on3"];

    update_led();
    //cont:;
    
    delay(500);
  } else {           //Connection stuffs here
    Serial.print("Connection Lost :(\nRe-");
    Wifi_connect(ssid_name, password);
    delay(5000);
  }
  client.end();
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
  digitalWrite(led3, (on3) ? HIGH : LOW);
}

bool isRepeat(int current_code){
  if((int)(millis()-last_ms)<200 && ir_code==current_code){
    Serial.print("Duplicate Code: ");
    Serial.println(ir_code);
    last_ms=millis();
    return true;
  }
  else{
    last_ms=millis();
    return false;
  }
  
}

bool inv(bool x){
  if(x)
    return false;
  else
    return true;
}

int req(String url){
  client.begin(url);
  return client.GET();
}

void Handle_ir_code(int ir_code){
  if(ir_code==302336){
      on0=inv(on0);
      update_led();
      (internet_access)?:goto skip_send_data; //Skip If There is no internet
      if(on0)
        req("http://localhost:81/api/flip/on0/true");
      else
        req("http://localhost:81/api/flip/on0/false");
    }
    if(ir_code==302337){
      on1=inv(on1);
      update_led();
      (internet_access)?:goto skip_send_data; //Skip If There is no internet
      if(on1)
        req("http://localhost:81/api/flip/on1/true");
      else
        req("http://localhost:81/api/flip/on1/false");
    }
    if(ir_code==302338){
      on2=inv(on2);
      update_led();
      (internet_access)?:goto skip_send_data; //Skip If There is no internet
      if(on2)
        req("http://localhost:81/api/flip/on2/true");
      else
        req("http://localhost:81/api/flip/on2/false");
    }
    if(ir_code==302339){
      on3=inv(on3);
      update_led();
      (internet_access)?:goto skip_send_data; //Skip If There is no internet
      if(on3)
        req("http://localhost:81/api/flip/on3/true");
      else
        req("http://localhost:81/api/flip/on3/false");
    }
    if(ir_code==302357){
      on0=false;on1=false;on2=false;on3=false;
      update_led();
      (internet_access)?:goto skip_send_data; //Skip If There is no internet
      req("http://localhost:81/api/flip/on0/false");
      req("http://localhost:81/api/flip/on1/false");
      req("http://localhost:81/api/flip/on2/false");
      req("http://localhost:81/api/flip/on3/false");
    }
    if(ir_code==302347){
      on0=true;on1=true;on2=true;on3=true;
      update_led();
      (internet_access)?:goto skip_send_data; //Skip If There is no internet
      req("http://localhost:81/api/flip/on0/true");
      req("http://localhost:81/api/flip/on1/true");
      req("http://localhost:81/api/flip/on2/true");
      req("http://localhost:81/api/flip/on3/true");
    }
    skip_send_data:;
}
