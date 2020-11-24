//Libraries needed to compile the code

#include <TM1637Display.h>
// https://github.com/avishorp/TM1637
#include <Thermistor.h>
// https://github.com/ItKindaWorks/libraries/tree/master/Thermistor

//These values are used, thinking about using an ATtiny85
#define pot   A3 //Analog potentiometer input
#define term  A2 //Thermistor analog input
#define rele  0  //Digital output for relay control
#define CLK   1  //TM1637 CLK pin
#define DIO   2  //TM1637 DIO pin

int tmp = 0, temp1, temp2 = -100, potval1, potval2 = -1;
bool cnt = 1;
Thermistor temp(term);
TM1637Display disp(CLK, DIO);

void setup() {
  pinMode(pot, INPUT);
  pinMode(rele, OUTPUT);
}

void loop() {
  temp1 = temp.getTemp();
  if (temp1 <= -10) temp1 = -9; //Limit of only 1 digit for negative numbers
  potval1 = analogRead(pot);
  potval1 = int(map(potval1,0,1022,10,40)); //Minimum value 10, maximum value 40

  if ((temp1 != temp2) || (potval1 != potval2)) {
    if (potval1 != potval2) disp.setBrightness(5,1);
    tmp = 0;
    cnt = 1;
    temp2 = temp1;
    potval2 = potval1;
    disp.showNumberDecEx(temp1,0b01000000,0,2,0);
    disp.showNumberDec(potval1,0,2,2);
  }
    
  if (cnt) tmp++;
    
  if (tmp >= 20) { //Wait 10 seconds (considering the 0.5s delay) to set the relay
    if (potval1 > temp1) {
      digitalWrite(rele,1);        
    } else {
      digitalWrite(rele,0);      
    }
    
    disp.setBrightness(0,1);
    disp.showNumberDec(potval1,0,2,2); //Apparently you have to set something for the display brightness to change state
    cnt = 0;
  }
  
  delay(500); //0.5 second delay for program flow control
}
