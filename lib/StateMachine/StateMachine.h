#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <Arduino.h>

struct StateMachine
{
  
  uint16_t clockwise = 0;
  uint16_t anticlockwise = 0;
  
  void update(uint8_t newState){
    switch (previousState)
    {
    case 0b00:
      update_00(newState);
      return;
    case 0b01:
      update_01(newState);
      return;
    case 0b10:
      update_10(newState);
      return;
    case 0b11:
      update_11(newState);
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
    if(anticlockwise > 0){
      vals |= 0b10;
      anticlockwise--;
    }
    return vals;
  }
private:

  uint8_t previousState = 0b11; // bit 0 = CLK (a), bit 1 = DT (b)

  void update_11(uint8_t newState){
    previousState = newState;
    if(0b10 == newState && clockwise < UINT16_MAX){
      clockwise++;
      return;
    }
    if(0b01 == newState && anticlockwise < UINT16_MAX){
      anticlockwise++;
      return;;
    }
  }

  void update_10(uint8_t newState){
    previousState = newState;
    if(0b00 == newState && clockwise < UINT16_MAX){
      clockwise++;
      return;
    }
    if(0b11 == newState && anticlockwise < UINT16_MAX){
      anticlockwise++;
      return;
    }
  }

  void update_00(uint8_t newState){
    previousState = newState;
    if(0b01 == newState && clockwise < UINT16_MAX){
      clockwise++;
      return;
    }
    if(0b10 == newState && anticlockwise < UINT16_MAX){
      anticlockwise++;
      return;
    }
  }

  void update_01(uint8_t newState){
    previousState = newState;
    if(0b11 == newState && clockwise < UINT16_MAX){
      clockwise++;
      return;
    }
    if(0b00 == newState && anticlockwise < UINT16_MAX){
      anticlockwise++;
      return;
    }
  }
};
#endif