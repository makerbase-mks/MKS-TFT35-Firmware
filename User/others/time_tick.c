#include "stm32f10x.h"
#include "time_tick.h"

unsigned int TimingDelay;


void SysTickInit(unsigned int HzPreSecond)
{
   if (SysTick_Config(SystemCoreClock / HzPreSecond))
    { 
        /* Capture error */ 
        while (1);
    }
}

void SysTickDelay(unsigned int nTime)
{ 
    TimingDelay = nTime;

    while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    { 
        TimingDelay--;
    }
}

/**-------------------------------------------------------
  * @函数名 SysTick_Handler
  * @功能   系统节拍定时器服务请求处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
    /*
void SysTick_Handler()
{
    _dwTickCount++;
  
    TimingDelay_Decrement();

    SysTick_Handler_User();
}
*/

unsigned int   getTick()
{
	return TimeIncrease;
}

unsigned int  getTickDiff(unsigned int curTick, unsigned int  lastTick)
{
	if(lastTick <= curTick)
	{
		return (curTick - lastTick) * TICK_CYCLE;
	}
	else
	{
		return (0xffffffff - lastTick + curTick) * TICK_CYCLE;
	}
}