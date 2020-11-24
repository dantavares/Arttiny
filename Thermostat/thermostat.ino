/***********************************************************
*     Termostato positivo, controlado por relê  V1.0       *
*                                                          * 
* Este projeto usa um termistor NTC 10k, como sensor de    *
* temperatura ambiente, um display TM1637 para exibir      *
* valores e um potênciometro de 100k para setar a          *
* temperatura desejada.                                    *
*                                                          *
* Use um aquecedor comum ligado ao relê, caso a            *                                               
* temperatura não seja a desejada, o relê irá ligar o      * 
* aquecedor, até que chegue na temperatura definida pelo   *
* potenciômetro. Os valores de temperatura ambiente e      * 
* temperatura desejada são exibiros no diplay, sendo os    *
* dois primeiros valores a temperatura a ambiente e os     *
* dois ultimos a demperatura desejada.                     *
* A ativação e desativação do aquecedor não                *
* é instantânea, isso é proposital, para que isso só       *
* ocorra quando a temperatura ambiente se estabilizou.     *
*                                                          *
* ATENÇÃO! Lembre-se de verificar se o relê suporta o      *                                            
* aquecedor ligado a ele!                                  *
*                                                          *  
* Programa desenvolvido por: Daniel Tavares                *
* dantavares@gmail.com                                     *
*                                                          *
* Você é livre para modificar e usar esse código, só peço  *
* que mantenha a referência do meu nome nele, obrigado     *
* por respeitar isso !                                     *
***********************************************************/

//Bibliotecas necessárias para compilar o código
#include <TM1637Display.h>
#include <Thermistor.h>

//Esses valores são usados, pensando em usar um ATtiny85
#define pot   A3 //Entrada analógica do potenciômetro
#define term  A2 //Entrada analógica do termistor
#define rele  0  //Saída digital para controle do relê
#define CLK   1  //Pino CLK do TM1637
#define DIO   2  //Pino DIO do TM1637

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
  if (temp1 <= -10) temp1 = -9; //Limitação de apenas 1 digito para números negativos
  potval1 = analogRead(pot);
  potval1 = int(map(potval1,0,1022,10,40)); //Valor mínimo 10, valor máximo 40

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
    
  if (tmp >= 20) { //Espera de 10 segundos (considerando o delay de 0,5s) para setar o relê
    if (potval1 > temp1) {
      digitalWrite(rele,1);        
    } else {
      digitalWrite(rele,0);      
    }
    
    disp.setBrightness(0,1);
    disp.showNumberDec(potval1,0,2,2); //Aparentemente tem que setar algo para o brilho do display mudar
    cnt = 0;
  }
  
  delay(500); //Delay de 0,5 segundos para controle de fluxo do programa
}
