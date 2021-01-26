/**
  *******************************************************
  * @file       remote.c/h
  * @brief      遥控器处理，利用大疆的接收机，通过串口协议进行数据
  *             传输，串口波特率为10000。此文件定义了遥控器相关的变量
  *             
  * 
  * @note       该任务通过串口中断启动，不是freertos任务
				目前，遥控器的热插拔稳定性较差，后续需要进一步改进

  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  *******************************************************
  */
#include "remote.h"

//遥控器数据上限，大于整个值说明出了问题
#define RC_CHANNAL_ERROR_VALUE 700


//make the data greater than 0
static int16_t RC_abs(int16_t value);

//遥控器变量
RC_ctrl_t rc_ctrl;
uint8_t teledata_rx[18];

//determine if the remote control data is error
uint8_t RC_data_is_error(void)
{
    //使用了goto语句，方便出错时统一处理遥控器数据归零
    if (RC_abs(rc_ctrl.rc.ch[0]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (RC_abs(rc_ctrl.rc.ch[1]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (RC_abs(rc_ctrl.rc.ch[2]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (RC_abs(rc_ctrl.rc.ch[3]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (rc_ctrl.rc.sleft == 0)
    {
        goto error;
    }
    if (rc_ctrl.rc.sright == 0)
    {
        goto error;
    }
    return 0;

error:
    rc_ctrl.rc.ch[0] = 0;
    rc_ctrl.rc.ch[1] = 0;
    rc_ctrl.rc.ch[2] = 0;
    rc_ctrl.rc.ch[3] = 0;
    rc_ctrl.rc.sleft = RC_DOWN;
    rc_ctrl.rc.sright = RC_DOWN;
    rc_ctrl.mouse.x = 0;
    rc_ctrl.mouse.y = 0;
    rc_ctrl.mouse.z = 0;
    rc_ctrl.mouse.press_l = 0;
    rc_ctrl.mouse.press_r = 0;
    rc_ctrl.key.v = 0;
	rc_ctrl.key.v2 = 0;
    return 1;
}



void SBUS_TO_RC(uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl)
{
	
    rc_ctrl->rc.ch[0] = ((int16_t)sbus_buf[0] | ((int16_t)sbus_buf[1] << 8)) & 0x07ff;        //!< Channel 0
    rc_ctrl->rc.ch[1] = ((sbus_buf[1] >> 3) | (sbus_buf[2] << 5)) & 0x07ff; //!< Channel 1
    rc_ctrl->rc.ch[2] = ((sbus_buf[2] >> 6) | (sbus_buf[3] << 2) |          //!< Channel 2
                         (sbus_buf[4] << 10)) & 0x07ff;
    rc_ctrl->rc.ch[3] = ((sbus_buf[4] >> 1) | (sbus_buf[5] << 7)) & 0x07ff; //!< Channel 3
    rc_ctrl->rc.sright = ((sbus_buf[5] >> 4) & 0x0003);      			            //!< Switch left
    rc_ctrl->rc.sleft = ((sbus_buf[5] >> 4) & 0x000C) >> 2;                  //!< Switch right
    rc_ctrl->mouse.x = sbus_buf[6] | (sbus_buf[7] << 8);                    //!< Mouse X axis
    rc_ctrl->mouse.y = sbus_buf[8] | (sbus_buf[9] << 8);                    //!< Mouse Y axis
    rc_ctrl->mouse.z = sbus_buf[10] | (sbus_buf[11] << 8);                  //!< Mouse Z axis
    rc_ctrl->mouse.press_l = sbus_buf[12];                                  //!< Mouse Left Is Press ?
    rc_ctrl->mouse.press_r = sbus_buf[13];                                  //!< Mouse Right Is Press ?
    rc_ctrl->key.v = sbus_buf[14] | (sbus_buf[15] << 8);                    //!< KeyBoard value
    //rc_ctrl->key.v2 = sbus_buf[16] | (sbus_buf[17] << 8);                 //NULL
	rc_ctrl->rc.ch[4] =  ((int16_t)sbus_buf[16] | ((int16_t)sbus_buf[17] << 8)) & 0x07FF;
	
	rc_ctrl->rc.ch[0]-=RC_CH_VALUE_OFFSET;
	rc_ctrl->rc.ch[1]-=RC_CH_VALUE_OFFSET;
	rc_ctrl->rc.ch[2]-=RC_CH_VALUE_OFFSET;
	rc_ctrl->rc.ch[3]-=RC_CH_VALUE_OFFSET;
	rc_ctrl->rc.ch[4]-=RC_CH_VALUE_OFFSET;
}	

//返回遥控器控制变量，通过指针传递方式传递信息
const RC_ctrl_t *get_remote_control_point(void)
{
    return &rc_ctrl;
}

static int16_t RC_abs(int16_t value)
{
    if (value > 0)
    {
        return value;
    }
    else
    {
        return -value;
    }
}


