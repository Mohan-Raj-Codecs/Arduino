#define MARK_EXCESS_MICROS    20 // recommended for the cheap VS1838 modules

#include <IRremote.h>

int IR_RECEIVE_PIN = 11;

//Vars
const int voli4 = 8208; const int vold4 = 8209; const int rch4 = 8224; const int lch4 = 8225; 
const int ok4 = 8240; const int power4 = 8204; const int mute4 = 8205; const int selec = 9999;
int ir_code = 0, last_ms = millis();
bool wheel_f=false; bool wheel_b=false; bool spray=false; bool seed=false; bool grass=false;
//PINS
int wheel_motor_f=3; int wheel_motor_b=4; int spray_motor=5; int seed_motor=6;int seed_motor_pwm=10; int grass_motor=9;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(wheel_motor_f,OUTPUT);
  pinMode(wheel_motor_b,OUTPUT);
  pinMode(spray_motor,OUTPUT);
  pinMode(seed_motor,OUTPUT);
  pinMode(seed_motor_pwm,OUTPUT);
  pinMode(grass_motor,OUTPUT);
  Serial.begin(9600);   // Status message will be sent to PC at 9600 baud
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
  delay(2000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {  // Grab an IR code
    if(isRepeat(IrReceiver.decodedIRData.decodedRawData)){
      ir_code = IrReceiver.decodedIRData.decodedRawData;
      goto cont;
    }
    
    ir_code = IrReceiver.decodedIRData.decodedRawData;

    Serial.println(ir_code);
    //else {
      //Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
      //Serial.println(ir_code);
    //}

    switch (ir_code) {
      case voli4: Serial.println("Vol Up"); wheel_f=inv(wheel_f); wheel_b=false; break;
      case vold4: Serial.println("Vol Down"); wheel_b=inv(wheel_b); wheel_f=false; break;
      case selec: Serial.println("Select"); grass=inv(grass); break;
      case rch4: Serial.println("Right Channel"); spray=inv(spray);break;
      case lch4: Serial.println("Left Channel"); seed=inv(seed); break;
      case ok4: Serial.println("OK"); seed=true; wheel_f=true; wheel_b=false; spray=true; grass=true;  break;
      case power4: Serial.println("Power"); seed=false; wheel_f=false; wheel_b=false; spray=false; grass=false; break;
      case mute4: Serial.println("Mute"); seed=true; wheel_f=true; wheel_b=false; spray=false; grass=false; break;
      default: Serial.println("Unknown Button");
    }
    print_data();
    update_motor();
    
    cont:;
    IrReceiver.resume();                            // Prepare for the next value
  }
}


bool inv(bool x){
  if(x)
    return false;
  else
    return true;
}

bool isRepeat(int current_code){
  if((int)(millis()-last_ms)<200 && ir_code==current_code){
    Serial.print("Duplicate Code: ");
    Serial.println(ir_code);
    last_ms=millis();
    return true;
  }
  else{
    last_ms=millis();
    return false;
  }
}

void print_data(){
  Serial.print("\nwheel forward: ");
  Serial.println(wheel_f);
  Serial.print("\nwheel backward: ");
  Serial.println(wheel_b);
  Serial.print("spray: ");
  Serial.println(spray);
  Serial.print("seed: ");
  Serial.println(seed);
  Serial.print("grass: ");
  Serial.println(grass);
  Serial.println();
}

void update_motor(){
  digitalWrite(wheel_motor_f,(wheel_f)?HIGH:LOW);
  if((wheel_f!=wheel_b) || (wheel_b==false)){
    digitalWrite(wheel_motor_b,(wheel_b)?HIGH:LOW);
  }
  else{
    Serial.println("Motor Short Protection :( ");
  }
  digitalWrite(spray_motor,(spray)?HIGH:LOW);
  seeder();
  //digitalWrite(seed_motor,(seed)?HIGH:LOW);
  digitalWrite(grass_motor,(grass)?HIGH:LOW);
}

void seeder(){
  if(seed){
    digitalWrite(seed_motor,HIGH);
    analogWrite(seed_motor_pwm,255);//Initial Torque
    delay(350);
    analogWrite(seed_motor_pwm,80);
    
  }
  else{
    digitalWrite(seed_motor,LOW);
    analogWrite(seed_motor_pwm,0);
  }  
}
