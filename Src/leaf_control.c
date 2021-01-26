#include "leaf_control.h"

extern void LED_arrow(uint8_t leaf_num);
extern void LED_on(uint8_t leaf_num);
extern void LED_off();
extern void LED_init();

static uint16_t a[5]={0,3,2,4,1};
void remote_control(void)
{
	R_display((uint16_t*)pwm_data,led_data_R);// R亮
	osDelay(60);
		if(rc_ctrl.rc.sleft==RC_MID)//左开关中间位
			{
				if(rc_ctrl.rc.sright==RC_UP)//右开关上位
				{
					LED_arrow(a[0]);
					osDelay(60);
				}		
				else if(rc_ctrl.rc.sright==RC_MID)//击中则右开关置中
				{
					LED_on(a[0]);
					HAL_Delay(60);
					LED_arrow(a[1]);
					osDelay(60);
				}
				else
				{
					LED_on(a[1]);
					osDelay(60);
					LED_arrow(a[2]);
				osDelay(60);	
			}
			}
		else if(rc_ctrl.rc.sleft==RC_UP)
			{
				if(rc_ctrl.rc.sright==RC_DOWN)
				{
						LED_on(a[2]);
						osDelay(60);
						LED_arrow(a[3]);
						osDelay(60);		
				}
				else if(rc_ctrl.rc.sright==RC_MID)
				{
						LED_on(a[3]);
						osDelay(60);
						LED_arrow(a[4]);
						osDelay(60);			
				}
				else
				{
						LED_on(a[4]);
						osDelay(60);
				}
			}
		else 
		{
			LED_init();
		}
}


