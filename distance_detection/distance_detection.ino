const int trig = 8;
const int echo = 9;
const int led = 13;

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,LOW);    //Initially LED is Off
  
  digitalWrite(trig,LOW);  //Initially We Doesn't Trigger Sound is Off
  delayMicroseconds(2);

  digitalWrite(trig,HIGH);   //Triggering Sound
  delayMicroseconds(10);
  digitalWrite(trig,LOW);    //Triggering OFF

  duration = pulseIn(echo,HIGH);  //We Get input from the Pulse pin 
  distance = duration*0.034/2;    //Calculating the Distance

  Serial.print(" Distance : ");
  Serial.println(distance);
  
  if(distance<25){
    digitalWrite(led,HIGH);
    delay(100);
  }
}
