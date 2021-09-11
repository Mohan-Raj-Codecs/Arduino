int ire=13;
int irr=A0;
float val;

void setup() {
  // put your setup code here, to run once:
  pinMode(ire,OUTPUT);
  pinMode(irr,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  
//  digitalWrite(ire,HIGH);
//  delay(1000);
//  digitalWrite(ire,LOW);                 //PullDown Resistor (100+100k)200k
//  delay(500);                            //PullUp Resitor 220 k
    Serial.println(analogRead(irr));
}
