#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#define SwitchPin 2 
int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

//RF
int SentMessage[4] = {0,0,0,0};
RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup() {
  Serial.begin(9600); 
  //RF
  pinMode(SwitchPin, INPUT_PULLUP); 
  digitalWrite(SwitchPin,HIGH);
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
  //Analog
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
}

void loop() {
 Read_Joy();
 Handle_Axis();
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  radio.write(SentMessage, sizeof(SentMessage));
  //delay(100);
  delay(100);
  
}

//Analog START
void Read_Joy(){
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
}

void Transmit(int a,int b,int c,int d){
    SentMessage[0]=a;
    SentMessage[1]=b;
    SentMessage[2]=c;
    SentMessage[3]=d;
    radio.write(SentMessage, sizeof(SentMessage));
}

void Handle_Axis(){
  Serial.println(SW_state);
  if(mapX>400 && mapY>400){
    Transmit(0,1,1,0);
    Serial.println("Quick Left");
  }
  else if(mapX>400 && mapY<-200){
    Transmit(1,0,0,1);
    Serial.println("Quick Right");
  }
  else if(mapX<-400){
    Transmit(1,0,1,0);
    Serial.println("Forward");
  }
  else if(mapX>400){
    Transmit(0,1,0,1);
    Serial.println("Reverse");
  }
  else if(mapY>400){
    Transmit(0,0,1,0);
    Serial.println("Left");
  }
  else if(mapY<-200){
    Transmit(1,0,0,0);
    Serial.println("Right");
  }
  else{
    Transmit(0,0,0,0);
    Serial.println("Stop");
  }
//Analog END

}