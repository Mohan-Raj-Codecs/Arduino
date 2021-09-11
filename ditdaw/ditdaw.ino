
int LED = 13;
int Inp = A0;
int di=100;
int da=200;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH);
  delay(di);
  digitalWrite(LED,LOW);
  delay(di);
  digitalWrite(LED,HIGH);
  delay(di);
  digitalWrite(LED,LOW);
  delay(di);
  digitalWrite(LED,HIGH);
  delay(di);
  digitalWrite(LED,LOW);
  delay(400);
  digitalWrite(LED,HIGH);
  delay(da);
  digitalWrite(LED,LOW);
  delay(da);
  digitalWrite(LED,HIGH);
  delay(da);
  digitalWrite(LED,LOW);
  delay(da);
  digitalWrite(LED,HIGH);
  delay(da);
  digitalWrite(LED,LOW);
  delay(da+200);  

}
