#include "delay.h"

//typedef uint8_t u8;
//typedef uint32_t u32;

uint8_t fac_us;

void delay_init(uint8_t SYSCLK)
{
    #if SYSTEM_SUPPORT_OS //?????? OS.
       uint32_t reload;
    #endif
    
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    //SysTick ??? HCLK
    fac_us=SYSCLK; //?????? OS,fac_us ?????
    
    #if SYSTEM_SUPPORT_OS //?????? OS.
        reload=SYSCLK; //???????? ??? K
        reload*=1000000/delay_ostickspersec; //?? delay_ostickspersec ??????
        //reload ? 24 ????,???:16777216,? 180M ?,?? 0.745s ??
        fac_ms=1000/delay_ostickspersec; //?? OS ?????????
        SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//?? SYSTICK ??
        SysTick->LOAD=reload; //? 1/OS_TICKS_PER_SEC ?????
        SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //?? SYSTICK
        #else
    #endif
}




 void delay_ms(int32_t nms) 
 {
  int32_t temp; 
  SysTick->LOAD = 8000*nms; 
  SysTick->VAL=0X00;//清空计数器 
  SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源 
  do 
  { 
       temp=SysTick->CTRL;//读取当前倒计数值 
  }
     while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达 
     
     SysTick->CTRL=0x00; //关闭计数器 
     SysTick->VAL =0X00; //清空计数器 
 }
 

void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told,tnow,tcnt=0;
    uint32_t reload=SysTick->LOAD; //LOAD ??
    ticks=nus*fac_us; //??????
    told=SysTick->VAL; //?????????
    while(1)
    {
        tnow=SysTick->VAL;
        if(tnow!=told)
        {
            if(tnow<told)tcnt+=told-tnow;//???? SYSTICK ??????????.
            else tcnt+=reload-tnow+told;
            told=tnow;
            if(tcnt>=ticks)break; //????/????????,???.
        }
    };
}
