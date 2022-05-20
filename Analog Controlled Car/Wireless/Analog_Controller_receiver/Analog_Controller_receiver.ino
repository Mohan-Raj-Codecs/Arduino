#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

//Customs
int LF=4;
int LR=5;
int RF=6;
int RR=7;
//RF
int ReceivedMessage[4] = {0,0,0,0}; // Used to store value received by the NRF24L01
RF24 radio(9,10); // NRF24L01 SPI pins. Pin 9 and 10 on the Nano
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup() {
  Serial.begin(9600); 
  
  pinMode(LF,OUTPUT);
  pinMode(LR,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RR,OUTPUT);
  //RF
  radio.begin(); // Start the NRF24L01
  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
  radio.startListening(); // Listen to see if information received
  
}

void loop() {
  catch_packets();
  Change(ReceivedMessage[0],ReceivedMessage[1],ReceivedMessage[2],ReceivedMessage[3]);
  //Serial.println(ReceivedMessage[0]);
  Serial.print(" a: ");
  Serial.print(ReceivedMessage[0]);
  Serial.print(" b: ");
  Serial.print(ReceivedMessage[1]);
  Serial.print(" c: ");
  Serial.print(ReceivedMessage[2]);
  Serial.print(" d: ");
  Serial.println(ReceivedMessage[3]);
  delay(100);
}


void Change(int a,int b,int c,int d){
  digitalWrite(LF,(a==1)?HIGH:LOW);
  digitalWrite(LR,(b==1)?HIGH:LOW);
  digitalWrite(RF,(c==1)?HIGH:LOW);
  digitalWrite(RR,(d==1)?HIGH:LOW);
}

void catch_packets(){
  if(radio.available()){
    radio.read(ReceivedMessage,sizeof(ReceivedMessage));
  }
}
