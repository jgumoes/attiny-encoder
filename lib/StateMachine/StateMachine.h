#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <Arduino.h>

namespace StateMachine
{
  
  int8_t clockwise = 0;
  int8_t anticlockwise = 0;
  
  /**
   * @brief DO NOT TOUCH OUTSIDE OF UNIT TESTS!
   * 
   */
  uint8_t previousState = 0b11; // bit 0 = CLK (a), bit 1 = DT (b)

  /**
   * @brief update the state machine with a new state. doesn't increment if the change is invalid (180* change), there is no change, or the count value is maxed out
   * 
   * @param newState bit 0 = CLK (a), bit 1 = DT (b)
   */
  void update(uint8_t newState){
    const uint8_t switchState = (previousState << 2) | newState;
    previousState = newState;
    
    switch (switchState)
    {
    case 0b0001:
      if(clockwise < INT8_MAX){
        clockwise++;
      }
      return;
    case 0b0010:
      if(anticlockwise < INT8_MAX){
        anticlockwise++;
      }
      return;
    case 0b0111:
      if(clockwise < INT8_MAX){
        clockwise++;
      }
      return;
    case 0b0100:
      if(anticlockwise < INT8_MAX){
        anticlockwise++;
      }
      return;
    case 0b1000:
      if(clockwise < INT8_MAX){
        clockwise++;
      }
      return;
    case 0b1011:
      if(anticlockwise < INT8_MAX){
        anticlockwise++;
      }
      return;
    case 0b1110:
      if(clockwise < INT8_MAX){
        clockwise++;
      }
      return;
    case 0b1101:
      if(anticlockwise < INT8_MAX){
        anticlockwise++;
      }
      return;
    
    default:
      break;
    }
  }

  /**
   * @brief returns a bit flag, i.e. 0b(anticlockwise > 0)(clockwise > 0). decrements the counts
   * 
   * @return uint8_t 
   */
  uint8_t take(){
    uint8_t vals = 0;
    if(clockwise > 0){
      vals = 1;
      clockwise--;
    }
    else{
      clockwise = 0;
    }
    if(anticlockwise > 0){
      vals |= 0b10;
      anticlockwise--;
    }
    else{
      anticlockwise = 0;
    }
    return vals;
  }
};
#endif