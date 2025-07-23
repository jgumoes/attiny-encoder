#include <Arduino.h>
#include <StateMachine.h>
#include <avr/io.h>

#define mask (uint8_t) 3

void setup() {
  /*
  setup timer0 to use normal mode and compare values in code,
  i.e. if timer >= halfPeriod || timerFlag
  */
 TCCR0A = 0;  // set mode to normal
 TCCR0B = 1;  // no prescale

  const uint8_t count = 10; // 8MHz/(2*f)
  bool signalState = 0;

  /*
  CLK in = PB0
  DT in = PB1
  */
  using namespace StateMachine;

  const uint8_t clockwiseOut = PB3;
  const uint8_t anticlockwiseOut = PB4;
  DDRB = (1<<clockwiseOut) | (1<<anticlockwiseOut);
  
  
  uint8_t ports;
  while(1){
    ports = PINB & mask;
    update(ports);

    if((TCNT0 >= count) || ((TIMSK & 0b10) > 0)){
      if(false == signalState){
        PINB |= (take() << PB3);
      }
      else{
        PINB &= 3;  // write pins low
      }
      signalState = !signalState;
      TCNT0 = 0;  // reset the timer
      TIMSK = 0b10; // reset the overflow flag
    }
  }
}

void loop() {
  // TODO: reset if the code reaches here
}
