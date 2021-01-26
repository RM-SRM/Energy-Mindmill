#ifndef REMOTE_H
#define REMOTE_H


/* -----------------------RC Channel Definition----------------------------*/
#define RC_CH_VALUE_MIN              ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET           ((uint16_t)1024)
#define RC_CH_VALUE_MAX              ((uint16_t)1684)

/* -----------------------RC Switch Definition-----------------------------*/
#define RC_SW_UP                     ((uint16_t)1)
#define RC_SW_MID                    ((uint16_t)3)
#define RC_SW_DOWN                   ((uint16_t)2)

/* -----------------------PC Key Definition--------------------------------*/
#define KEY_PRESSED_OFFSET_W         ((uint16_t)0x01<<0)
#define KEY_PRESSED_OFFSET_S         ((uint16_t)0x01<<1)
#define KEY_PRESSED_OFFSET_A 		 ((uint16_t)0x01<<2)
#define KEY_PRESSED_OFFSET_D         ((uint16_t)0x01<<3)
#define KEY_PRESSED_OFFSET_Q         ((uint16_t)0x01<<4)
#define KEY_PRESSED_OFFSET_E         ((uint16_t)0x01<<5)
#define KEY_PRESSED_OFFSET_SHIFT     ((uint16_t)0x01<<6)
#define KEY_PRESSED_OFFSET_CTRL      ((uint16_t)0x01<<7)

#define  RC_FRAME_LENGTH                            18u

/* ----------------------- RC Switch Definition----------------------------- */
#define RC_UP ((uint8_t)1)
#define RC_MID ((uint8_t)3)
#define RC_DOWN ((uint8_t)2)

#include "main.h"

/* ----------------------- Data Struct ------------------------------------- */
typedef __packed struct
{
        __packed struct
        {
                int16_t ch[5];
                char sleft;
				char sright;
        } rc;
        __packed struct
        {
                int16_t x;
                int16_t y;
                int16_t z;
                uint8_t press_l;
                uint8_t press_r;
        } mouse;
        __packed struct
        {
                uint16_t v;
								uint16_t v2;
        } key;

} RC_ctrl_t;

extern RC_ctrl_t rc_ctrl;
extern uint8_t teledata_rx[18];

extern const RC_ctrl_t *get_remote_control_point(void);
uint8_t RC_data_is_error(void);
void SBUS_TO_RC(uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl);

#endif
