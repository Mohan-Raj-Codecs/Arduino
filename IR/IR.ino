int CLK=8;
int dat=A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK,OUTPUT);
  pinMode(dat,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(CLK,HIGH);
  delay(100);
  digitalWrite(CLK,LOW);
  delay(100);
  analogWrite(dat,200);
  digitalWrite(1,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
}
