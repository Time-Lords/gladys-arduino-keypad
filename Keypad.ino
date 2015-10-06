#include <Keypad.h>
#include <RCSwitch.h>

const int transmitPin = 10;                 // Transmit pin
const char keypadResetKey = '*';            // Reset key
const char keypadSubmitKey = '#';           // Submit key
const byte keypadRows = 4;                  // Number row of keypad
const byte keypadCols = 3;                  // Number col of keypad

char keypadKeys[keypadRows][keypadCols] = { // Map of keyPad
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte keypadRowPins[keypadRows] = {9,8,7,6}; // Row pins of keypad
byte keypadColPins[keypadCols] = {5,4,3};   // Col pins of keypad

int keypadPos = 0;                          // Current position
char keypadCode[4] = {};                    // Current code

Keypad keypad = Keypad( makeKeymap(keypadKeys), keypadRowPins, keypadColPins, keypadRows, keypadCols );
RCSwitch transmit = RCSwitch();

void transmitSetup(){
  transmit.enableTransmit(transmitPin);
}

void transmitSend(char* code){
  transmit.send((int) strtol(code, (char **)NULL, 10), 16);
}

void keypadSend(char* code){
  transmitSend(code);
  Serial.println(code);
}

void keypadReset(){
  memset(keypadCode, 0, keypadPos);
  keypadPos=0;
}

void keypadLoop(){
  char key = keypad.getKey();
  if(!key){
    return;
  }else if(key == keypadResetKey){
    keypadReset();
  }else if(key == keypadSubmitKey){
    keypadSend(keypadCode);
    keypadReset();
  }else{
     keypadCode[keypadPos] = key;
     keypadPos++;
  }
}

void setup() {
  Serial.begin(9600);
  transmitSetup();
}

void loop() {
  keypadLoop();
}
