#include "LED.h"

volatile uint32_t pwm_data[18000]; //宽的是706个灯左右，706*24=16944，再给些余量
volatile uint32_t pwm_data_0[14200]; // 窄的是590个灯，590*24=14160，再给些余量
volatile uint32_t pwm_data_R[1920]; //80个灯

//高位到低位
//leaf_1 DMA
void data_trans_A0(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len)
{
	for(int16_t i=0;i<len;i++)
	{
		for(uint8_t j=0;j<3;j++)//三色灯
		{
			for(uint8_t k=0;k<8;k++)//8bit
			{
				pwm_data1[(i*3+j)*8+k]=(led_data[i*3+j]&(0x80>>k))?BIT1:BIT0;//占空比的输入
			}
		}
	}
	for(uint16_t i=0;i<300;i++)
	{
		pwm_data1[len*3*8+i]=0;
	}
	HAL_TIM_PWM_Start_DMA(&htim5,TIM_CHANNEL_1,pwm_data1,len*24+300);//+300的余量
}

//leaf_2 DMA
void data_trans_A1(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len)
{
		for(int16_t i=0;i<len;i++)
	{
		for(uint8_t j=0;j<3;j++)
		{
			for(uint8_t k=0;k<8;k++)
			{
				pwm_data1[(i*3+j)*8+k]=(led_data[i*3+j]&(0x80>>k))?BIT1:BIT0;
			}
		}
	}
	for(uint16_t i=0;i<300;i++)
	{
		pwm_data[len*3*8+i]=0;
	}
	HAL_TIM_PWM_Start_DMA(&htim5,TIM_CHANNEL_2,pwm_data1,len*24+300);
}
//leaf_3 DMA
void data_trans_A2(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len)
{
		for(int16_t i=0;i<len;i++)
	{
		for(uint8_t j=0;j<3;j++)
		{
			for(uint8_t k=0;k<8;k++)
			{
				pwm_data1[(i*3+j)*8+k]=(led_data[i*3+j]&(0x80>>k))?BIT1:BIT0;
			}
		}
	}
	for(uint16_t i=0;i<300;i++)
	{
		pwm_data[len*3*8+i]=0;
	}
	HAL_TIM_PWM_Start_DMA(&htim5,TIM_CHANNEL_3,pwm_data1,len*24+300);
}

//leaf_4 DMA
void data_trans_A3(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len)
{
		for(int16_t i=0;i<len;i++)
	{
		for(uint8_t j=0;j<3;j++)
		{
			for(uint8_t k=0;k<8;k++)
			{
				pwm_data1[(i*3+j)*8+k]=(led_data[i*3+j]&(0x80>>k))?BIT1:BIT0;
			}
		}
	}
	for(uint16_t i=0;i<300;i++)
	{
		pwm_data1[len*3*8+i]=0;
	}
	HAL_TIM_PWM_Start_DMA(&htim5,TIM_CHANNEL_4,pwm_data1,len*24+300);
}



	
//lead_5 DMA
void data_trans_I5(uint16_t pwm_data1[],volatile uint8_t led_data[], int32_t len)//DMA1设置的是WORD，DMA2设置的是HALF WORD，所以是16bit；
{
	for(int16_t i=0;i<len;i++)
	{
		for(uint8_t j=0;j<3;j++)
		{
			for(uint8_t k=0;k<8;k++)
			{
				pwm_data1[(i*3+j)*8+k]=(led_data[i*3+j]&(0x80>>k))?BIT1_1:BIT0_0;
			}
		}
	}
	for(uint16_t i=0;i<300;i++)
	{
		pwm_data1[len*3*8+i]=0;
	}
	HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_1, (uint32_t *)pwm_data1,len*24+300);
}



volatile uint8_t led_leaf_off[2130]={
	0
};

volatile uint8_t led_leaf_arrow[2130]={\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
Black,Black,Color,Color,Color,Black,\
\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
Color,Color,Color,Black,Black,Black,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color\
};

// _0的就是窄条，中间只有五灯条
volatile uint8_t led_leaf_arrow_0[1770]={
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
Black,Black,Black,Color,Color,Color,\
\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
Black,Color,Color,Color,Black,Black,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color\
};
           
volatile uint8_t led_leaf_on[2130]={\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
};


volatile uint8_t led_leaf_on_0[1770]={\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\

};

volatile uint8_t led_data_R[240]={\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
Color,Color,Color,Color,Color,Color,Color,Color,Color,Color,\
};

void LED_on(uint8_t leaf_num)
{
	switch (leaf_num)
	{
		case 0:
			data_trans_A0((uint32_t *)pwm_data,led_leaf_on_0,590);
      osDelay(20);
		break;
		case 1:
			data_trans_A1((uint32_t *)pwm_data,led_leaf_on,706);
      osDelay(20);
		break;
		case 2:
			data_trans_A2((uint32_t *)pwm_data,led_leaf_on,706);
      osDelay(20);
		break;
		case 3:
			data_trans_A3((uint32_t *)pwm_data,led_leaf_on,706);
      osDelay(20);
		break;
		case 4:
			data_trans_I5((uint16_t *)pwm_data,led_leaf_on,706);
      osDelay(20);
		break;
	}
}

void LED_arrow(uint8_t leaf_num)
{
	switch (leaf_num)
	{
		case 0:
		data_trans_A0((uint32_t *)pwm_data,led_leaf_arrow_0	,590);
		break;
		case 1:
		data_trans_A1((uint32_t *)pwm_data,led_leaf_arrow,706);
		break;
		case 2:
		data_trans_A2((uint32_t *)pwm_data,led_leaf_arrow,706);
		break;
		case 3:
		data_trans_A3((uint32_t *)pwm_data,led_leaf_arrow,706);
		break;
		case 4:
		data_trans_I5((uint16_t *)pwm_data,led_leaf_arrow,706);
		break;
	}

}


void R_display(volatile uint16_t pwm_data_R[],volatile uint8_t led_data_R[])
{
	for(int16_t i=0;i<LED_R;i++)
	{
		for(uint8_t j=0;j<3;j++)
		{
			for(uint8_t k=0;k<8;k++)
			{
				pwm_data_R[(i*3+j)*8+k]=(led_data_R[i*3+j]&(0x80>>k))?BIT1_1:BIT0_0;
			}
		}
	}
	for(uint16_t i=0;i<20;i++)
	{
		pwm_data_R[LED_R*3*8+i]=0;
	}
	HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_2, (uint32_t *)pwm_data_R,LED_R*24+20);
}



extern void LED_init()
{
	data_trans_A0((uint32_t *)pwm_data_0,led_leaf_off,590);
	osDelay(20);
	data_trans_A1((uint32_t *)pwm_data,led_leaf_off,706);
	osDelay(20);
	data_trans_A2((uint32_t *)pwm_data,led_leaf_off,706);
	osDelay(20);
	data_trans_A3((uint32_t *)pwm_data,led_leaf_off,706);
	osDelay(20);
	data_trans_I5((uint16_t *)pwm_data,led_leaf_off,706);
	osDelay(20);
}
