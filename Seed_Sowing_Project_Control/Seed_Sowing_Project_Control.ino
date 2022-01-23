#define MARK_EXCESS_MICROS    20 // recommended for the cheap VS1838 modules

#include <IRremote.h>

int IR_RECEIVE_PIN = 11;

//Var here
const int voli4 = 8208; const int vold4 = 8209; const int rch4 = 8224; const int lch4 = 8225; 
const int ok4 = 8240; const int power4 = 8204; const int mute4 = 8205;
int ir_code = 0, last_ms = millis();
bool wheel=false; bool spray=false; bool seed=false; bool grass=false;
//PINS
int wheel_motor=3; int spray_motor=5; int seed_motor=6; int grass_motor=9;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(wheel_motor,OUTPUT);
  pinMode(spray_motor,OUTPUT);
  pinMode(seed_motor,OUTPUT);
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
      case voli4: Serial.println("Vol Up"); wheel=inv(wheel); break;
      case vold4: Serial.println("Vol Down"); grass=inv(grass); break;
      case rch4: Serial.println("Right Channel"); spray=inv(spray);break;
      case lch4: Serial.println("Left Channel"); seed=inv(seed); break;
      case ok4: Serial.println("OK"); seed=true; wheel=true; spray=true; grass=true;  break;
      case power4: Serial.println("Power"); seed=false; wheel=false; spray=false; grass=false; break;
      case mute4: Serial.println("Mute"); seed=true; wheel=true; spray=false; grass=false; break;
      default: Serial.println("Unknown Button");
    }
    p_data();
    motor_update();
    
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

void p_data(){
  Serial.print("\nwheel: ");
  Serial.println(wheel);
  Serial.print("spray: ");
  Serial.println(spray);
  Serial.print("seed: ");
  Serial.println(seed);
  Serial.print("grass: ");
  Serial.println(grass);
  Serial.println();
}

void motor_update(){
  digitalWrite(wheel_motor,(wheel)?HIGH:LOW);
  digitalWrite(spray_motor,(spray)?HIGH:LOW);
  digitalWrite(seed_motor,(seed)?HIGH:LOW);
  digitalWrite(grass_motor,(grass)?HIGH:LOW);
}
