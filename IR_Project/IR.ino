int inp=A0;
float input,volt;
int out=9;
bool on = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inp,INPUT);
  pinMode(out,OUTPUT);
  bool inv(bool oni);  //Prototype Declaration
}

void loop() {
  // put your main code here, to run repeatedly:
  input=analogRead(inp);
  volt=(input*5.0)/1024.0;
  //Serial.print("voltage is : ");
  //Serial.println(volt);
    
  if(volt<1){
    on=inv(on);
    delay(100);
    }
  
  if(on){
    digitalWrite(out,HIGH);}
  else{
    digitalWrite(out,LOW);}

}


bool inv(bool oni){
  if(oni)
    oni=false;
  else
    oni=true;   
  return oni;
}
