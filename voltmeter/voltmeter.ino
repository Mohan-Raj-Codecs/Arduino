int in=A0;
float input;
float volt;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  input=analogRead(in);
  volt=(input*5.0)/1024.0;
  Serial.print("voltage is : ");
  Serial.println(volt);
}
