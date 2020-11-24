#include <IRremote.h>
//https://github.com/z3t0/Arduino-IRremote

/* 
* These hexadecimal codes must be discovered using an Arduio UNO first. 
* Uncomment the serial output lines, and use the serial monitor to discover the code, 
* pressing the desired remote control key.
*/

#define IR_OnOff 0xFFA25D
#define IR_MinPw 0xFF30CF
#define IR_MedPw 0xFF18E7
#define IR_FulPw 0xFF7A85

const int OutPin1 = 0; //Primeiro pino de saida, total de 3
int lstpos = OutPin1;
bool OnOff = 0;   //Inicialmente Desligado
IRrecv irrecv(3); //Pino do sensor IR
decode_results results;

void setup()
{
  for (int i = 0; i <= 3; i++)
    pinMode(OutPin1 + i, OUTPUT);
  //Uncomment the line below to find the hex code on an UNO Arduino  
  //Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  bool valid = 0;
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case IR_OnOff:
        OnOff = !OnOff;
        valid = 1;
        break;

      case IR_MinPw:
        lstpos = OutPin1;
        valid = 1;
        break;

      case IR_MedPw:
        lstpos = OutPin1 + 1;
        valid = 1;
        break;

      case IR_FulPw:
        lstpos = OutPin1 + 2;
        valid = 1;
        break;
    }

    if (valid) {
      for (int i = 0; i <= 3; i++)
        digitalWrite(OutPin1 + i, LOW);

      digitalWrite(lstpos, OnOff);
      valid = 0;
    }
    //Uncomment the line below to find the hex code on an UNO Arduino
    //Serial.print("0x"); Serial.println(results.value, HEX);
    irrecv.resume();
    delay_ten_us(15000);
  }
}

void delay_ten_us(uint16_t us) {
  #define NOP __asm__ __volatile__ ("nop")
  uint8_t timer;
  while (us != 0) {
    for (timer = 0; timer <= 25; timer++) {
      NOP;
      NOP;
    }
    NOP;
    us--;
  }
}
