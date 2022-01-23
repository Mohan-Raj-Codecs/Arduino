#define MARK_EXCESS_MICROS    20 // recommended for the cheap VS1838 modules

#include <IRremote.h>

#if defined(ESP32)
int IR_RECEIVE_PIN = 15;
#else
int IR_RECEIVE_PIN = 11;
#endif

//Var here
int ir_code = 0, last_ms = millis();

//Prototype
bool inv(bool x);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

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

    cont:;
    IrReceiver.resume();                            // Prepare for the next value
  }
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
