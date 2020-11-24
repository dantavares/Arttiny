/* Ver 2.1
 *  
 * Este programa usa um ATtiny85 para inverter o sinal digital de um botão físico por 100ms,
 * simulando um toque, quando detectado um comando de um controle remoto, préviamente programado.
 * Com isso é possível usar um controle remoto por infra vermelho, em um equipamento que não 
 * tenha um. Em geral por ser usado qualquer controle remoto IR, inclusive uma tecla que não é
 * usada (ou pouco usada), não tendo necessidade de ter um controle remoto exclusivo para ele.
 * 
 * Para programar o controle remoto:
 * 1º - Precione o botão físico e segure
 * 2º - Precione a tecla desejada do controle remoto
 * 3º - Continue segurando por 2 segundos
 * 4º - Solte o botão físico
 * 5º - Faça o teste, se necessário repita o procedimento
 * 
 * O código da tecla será gravado permanentemente, até que uma nova tecla seja reprogramada.
 */

#include <IRremote.h>
#include <EEPROM.h>

const byte SW = 0;      //Pino do botao
const byte IrPin = 1;   //Pino do sensor IR 
const bool NorSta = 1;  //Estado normal do botão: 1 para alta ou 0 para baixa

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

//Código para gravar e ler na EEPROM
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

//Código do delay
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
