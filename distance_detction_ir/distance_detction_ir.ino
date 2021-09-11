int Object=6;
int Yes;
int led=13;

void setup() {
  // put your setup code here, to run once:
  pinMode(Object,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Yes=digitalRead(Object);
  
  if(digitalRead(Object)==LOW){
    digitalWrite(led,HIGH);
    delay(10); 
  }
  else{
    digitalWrite(led,LOW);
    delay(10);
  }

  Serial.println(Yes);
}
