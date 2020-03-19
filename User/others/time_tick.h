#ifndef _TIME_TICK_H_
#define _TIME_TICK_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif



#define TICK_CYCLE		1 //ms

extern volatile unsigned int TimeIncrease;

void SysTick_Handler_User();

void SysTickInit(unsigned int HzPreSecond);

unsigned int   getTick();

unsigned int  getTickDiff(unsigned int lastTick, unsigned int  curTick);



#if defined(__cplusplus)
}
#endif

#endif
