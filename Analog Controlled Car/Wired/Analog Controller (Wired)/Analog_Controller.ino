int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

//Customs
int LF=8;
int LR=9;
int RF=10;
int RR=11;

void setup() {
  Serial.begin(9600); 
  
  pinMode(LF,OUTPUT);
  pinMode(LR,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RR,OUTPUT);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
}

void loop() {
  Read_Joy();
  Handle_Axis();

  /*Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);*/

  delay(100);
  
}

void Read_Joy(){
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
}

void Change(int a,int b,int c,int d){
  digitalWrite(LF,(a==1)?HIGH:LOW);
  digitalWrite(LR,(b==1)?HIGH:LOW);
  digitalWrite(RF,(c==1)?HIGH:LOW);
  digitalWrite(RR,(d==1)?HIGH:LOW);
}

void Handle_Axis(){
  Serial.println(SW_state);
  if(mapX>400 && mapY>400){
    Change(0,1,1,0);
    Serial.println("Quick Left");
  }
  else if(mapX>400 && mapY<-200){
    Change(1,0,0,1);
    Serial.println("Quick Right");
  }
  else if(mapX<-400){
    Change(1,0,1,0);
    Serial.println("Forward");
  }
  else if(mapX>400){
    Change(0,1,0,1);
    Serial.println("Reverse");
  }
  else if(mapY>400){
    Change(0,0,1,0);
    Serial.println("Left");
  }
  else if(mapY<-200){
    Change(1,0,0,0);
    Serial.println("Right");
  }
  else{
    Change(0,0,0,0);
    Serial.println("Stop");
  }




}