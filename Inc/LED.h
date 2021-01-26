#ifndef _LED_H
#define _LED_H

#include "stm32f4xx_hal.h"
#include "tim.h"
#include "dma.h"
#include "delay.h"
#include "cmsis_os.h"
#include "remote.h"


#define BIT0 21 // ռ�ձ�1/3Ϊ0��
#define BIT1 71	// ռ�ձ�2/3Ϊ0��
#define BIT0_0 42  //���ڼ�������Ϊ200��DMA1��Ϊ100����������һ��
#define BIT1_1 142

#define G 0xff,0,0 // 24bit һ����ɫ�ĵ�8bit��G,R,B˳��
#define R 0,0xff,0
#define B 0,0,0xff

#define Color 0,0,0x0c//��ֵ��С���Ըı�����
#define Black 0,0,0
//don't use 0xff power can't support

#define LED_R 80

//�����߼���DMA���� 
void data_trans_A0(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len);
void data_trans_A1(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len);
void data_trans_A2(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len);
void data_trans_A3(uint32_t pwm_data1[],volatile uint8_t led_data[], int32_t len);
void data_trans_I5(uint16_t pwm_data1[],volatile uint8_t led_data[], int32_t len);

//
 
extern volatile uint32_t pwm_data[18000];
extern volatile uint32_t pwm_data_0[14200];
extern volatile uint32_t pwm_data_R[1920];
//extern volatile uint8_t led_leaf_arrow[2130];
//extern volatile uint8_t led_leaf_arrow_0[1770];
extern volatile uint8_t led_leaf_on[2130];
//extern volatile uint8_t led_leaf_on_0[1770];
//extern volatile uint8_t led_leaf_off[2130];
extern volatile uint8_t led_data_R[240];
//

//���ƿ��Ƴ���
void LED_arrow(uint8_t leaf_num);
void LED_on(uint8_t leaf_num);
void LED_off();
void LED_init();
void R_display(volatile uint16_t pwm_data_R[],volatile uint8_t led_data_R[]);
//
	
#endif
