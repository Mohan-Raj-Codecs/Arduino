

int inp=A0;
float input,volt;
int out=9;
int bulb=A1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inp,INPUT);
  pinMode(out,OUTPUT);
  pinMode(bulb,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(bulb,0);
  digitalWrite(out,LOW);
  input=analogRead(inp);
  volt=(input*5.0)/1024.0;
  Serial.print("voltage is : ");
  Serial.println(volt);
  if(volt<1){
    digitalWrite(out,HIGH);
    analogWrite(bulb,150);
    delay(3000);
    }

}
