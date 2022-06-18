#include <BluetoothSerial.h>

#define ledPIN 2
BluetoothSerial SerialBT;
byte BTData;

//Customs
int LF=27;
int LR=26;
int RF=25;
int RR=33;

int sec = millis();

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup()
{
  pinMode(LF,OUTPUT);
  pinMode(LR,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RR,OUTPUT);

  pinMode(ledPIN, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
  
}

void loop()
{

  if(SerialBT.available())
  {
    BTData = SerialBT.read();
    Serial.write(BTData);
    sec=millis();
  }
  if((millis()-sec)>100){
    Serial.println("IDLE");
    BTData=0;
  }
  
  Handle();
  
}

void Change(int a,int b,int c,int d){
  digitalWrite(LF,(a==1)?HIGH:LOW);
  digitalWrite(LR,(b==1)?HIGH:LOW);
  digitalWrite(RF,(c==1)?HIGH:LOW);
  digitalWrite(RR,(d==1)?HIGH:LOW);
}

void Handle(){
  
  
  if(BTData == 'W' ){
    Change(1,0,1,0);
    Serial.println("Forward");
  }
  else if(BTData == 'E'){
    Change(0,1,0,1);
    Serial.println("Reverse");
  }
  else if(BTData == 'S'){
    Change(0,0,1,0);
    Serial.println("Left");
  }
  else if(BTData == 'N'){
    Change(1,0,0,0);
    Serial.println("Right");
  }
  else if(BTData == '2'){
    Change(0,1,1,0);
    Serial.println("Quick Left");
  }
  else if(BTData == '4'){
    Change(1,0,0,1);
    Serial.println("Quick Right");
  }
  
  else{
    Change(0,0,0,0);
    Serial.println("Stop");
  }
  
}