#include <IRremote.h>
//https://github.com/z3t0/Arduino-IRremote

#include <EEPROM.h>
//https://github.com/Chris--A/EEPROM

const byte SW = 0;      //Pin to be connected in parallel to the button
const byte IrPin = 1;   //CI Pin Infrared Sensor

const bool NorSta = 1;  //Normal button state: 1 for high or 0 for low

IRrecv irrecv(IrPin);   
decode_results results;
unsigned long IrCode;

void setup() {
  IrCode = EEPROM_readlong(0);
  irrecv.enableIRIn();
  pinMode(SW, OUTPUT);
  digitalWrite(SW, NorSta);
}

void loop() {
  const uint16_t delay1 = 10000;
  const uint16_t delay2 = 2000;
  if (irrecv.decode(&results)) {
    if (NorSta != digitalRead(SW)) {
      nop_delay(delay1*2);
      if (NorSta != digitalRead(SW)) {
        IrCode = results.value;
        EEPROM_writelong(0, IrCode);
      }
    }
    else
      if (results.value == IrCode) {
        digitalWrite(SW, !NorSta);
        nop_delay(delay2);
        digitalWrite(SW, NorSta);
        nop_delay(delay1);
      } 
    irrecv.resume();
    }
}

unsigned long EEPROM_readlong(int address) {
  unsigned long dword = EEPROM_readint(address);
  dword = dword << 16;
  dword = dword | EEPROM_readint(address+2);
  return dword;
}
void EEPROM_writeint(int address, int value) {
  EEPROM.write(address, highByte(value));
  EEPROM.write(address+1 ,lowByte(value));
}
void EEPROM_writelong(int address, unsigned long value) {
  EEPROM_writeint(address+2, word(value));
  value = value >> 16;
  EEPROM_writeint(address, word(value));
}
unsigned int EEPROM_readint(int address) {
  unsigned int word = word(EEPROM.read(address), EEPROM.read(address+1));
  return word;
}

void nop_delay(uint16_t us) {
  #define NOP __asm__ __volatile__ ("nop")
  while (us != 0) {
    for (uint8_t t = 0; t <= 50; t++) {
      NOP;
    }
    NOP;
    us--;
  }
}
