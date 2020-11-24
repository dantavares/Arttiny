#include <avr/sleep.h>
#include <avr/interrupt.h>

const int sync_pin = 3;  //power button repurposed for sync button (pin 5 on the module), don't change it!
const int data_pin = 2;  //data line (pin 6 on the module)
const int clock_pin = 1; //clock line (pin 7 on module) 

// All known commands are in the "Control bus protocol" file
int led_cmd[10]  = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0}; //Activates/initialises the LEDs, leaving the center LED lit. 
int sync_cmd[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}; //Initiates the sync process.

void sendData(int cmd_do[]) {
  pinMode(data_pin, OUTPUT);
  digitalWrite(data_pin, LOW);  //start sending data.
  int prev = 1;
  for (int i = 0; i < 10; i++) {
    while (prev == digitalRead(clock_pin)) {} //detects change in clock
    prev = digitalRead(clock_pin);
    // should be after downward edge of clock, so send bit of data now
    digitalWrite(data_pin, cmd_do[i]);

    while (prev == digitalRead(clock_pin)) {} //detects upward edge of clock
    prev = digitalRead(clock_pin);
  }
  digitalWrite(data_pin, HIGH);
  pinMode(data_pin, INPUT);
}

void sleep() {
    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin(3)
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement
    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep
    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on
    sei();                                  // Enable interrupts
}

ISR(PCINT0_vect) { // This function will be executed after ATtiny wake up
  sendData(sync_cmd);      
}

void delay_us(uint16_t us) {
  #define NOP __asm__ __volatile__ ("nop")
  while (us != 0) {
    for (uint8_t timer = 0; timer <= 25; timer++) {
      NOP;
      NOP;
    }
    NOP;
    us--;
  }
}

void setup() {
  pinMode(sync_pin, INPUT);
  digitalWrite(sync_pin, HIGH);
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  delay_us(2000);
  sendData(led_cmd);
}

void loop() {
  if (!(digitalRead(sync_pin))) { // Will only sleep if the sync button is not being pressed.
    sleep();
  }
}
