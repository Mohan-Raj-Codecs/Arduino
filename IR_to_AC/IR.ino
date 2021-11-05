//Nippy Embedded
int inp=A1;
float input,volt;
int out=8;
int copy_out=7;
int net=4;
bool on = false;

int d1,d2,d3;
float f1,f2,f3;
bool b1,b2;
//Nippy Embed End

void setup() {
  //Nippy Embedded
  pinMode(inp,INPUT);
  pinMode(out,OUTPUT);
  pinMode(copy_out,OUTPUT);
  pinMode(net,INPUT);
  digitalWrite(net,HIGH);
  bool inv(bool oni);  //Prototype Declaration
  Serial.begin(9600);
  //Nippy Embed End
}

void loop() {
   // Nippy Embedded
  input=analogRead(inp);
  volt=(input*5.0)/1024.0;
  //Serial.print("voltage is : ");
  //Serial.println(volt);
  if(volt<3){
    on=inv(on);
    delay(100);
    }
  d1=digitalRead(net);
  Serial.println(d1);
  
  if(on){
    digitalWrite(out,HIGH);
    digitalWrite(copy_out,HIGH);}
  else{
    digitalWrite(out,LOW);
    digitalWrite(copy_out,LOW);}
  //Nippy Embed End
}


bool inv(bool oni){
  if(oni)
    oni=false;
  else
    oni=true;   
  return oni;
}
