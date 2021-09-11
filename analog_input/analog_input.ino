int led=13;
int inp=A0;
int volt=0;
int voltage=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(inp,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  volt=analogRead(inp);
  Serial.print("Voltage at Joint : ");
  voltage=(volt/1023)*5;                        //Converting 3 bit numbers to Voltage
  Serial.println(voltage);
  if(voltage>3){ digitalWrite(led,HIGH); }    
  else{ digitalWrite(led,LOW); }
  delay(500);
}
