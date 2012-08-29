#ifndef _PWM_h
#define _PWM_h

//Modes
#define SINGLE_EDGE_CONTROL   1
#define DOUBLE_EDGE_CONTROL   2

#define _PWM_DEBUG

#ifdef _PWM_DEBUG
#define PWM_DEBUG(a) a
#else
#define PWM_DEBUG(a)
#endif

#define PWM_OUT_1_ON    0x01
#define PWM_OUT_2_ON    0x02
#define PWM_OUT_3_ON    0x04
#define PWM_OUT_4_ON    0x08
#define PWM_OUT_5_ON    0x10
#define PWM_OUT_6_ON    0x20

#define PWM_OUT_1_OFF   0x00
#define PWM_OUT_2_OFF   0x00
#define PWM_OUT_3_OFF   0x00
#define PWM_OUT_4_OFF   0x00
#define PWM_OUT_5_OFF   0x00
#define PWM_OUT_6_OFF   0x00

#define PWM_OUT_1_MUX() ( PINSEL0_bit.P0_0 = 0x02 )
#define PWM_OUT_2_MUX() ( PINSEL0_bit.P0_7 = 0x02 )
#define PWM_OUT_3_MUX() ( PINSEL0_bit.P0_1 = 0x02 )
#define PWM_OUT_4_MUX() ( PINSEL0_bit.P0_8 = 0x02 )
#define PWM_OUT_5_MUX() ( PINSEL1_bit.P0_21 = 0x01 )
#define PWM_OUT_6_MUX() ( PINSEL0_bit.P0_9 = 0x02 )


typedef struct
{
  uint16 Out1D;
  uint16 Out2D;
  uint16 Out3D;
  uint16 Out4D;
  uint16 Out5D;
  uint16 Out6D;
} PwmOutD_t;

Status_t Pwm_Init(uint8 Mode, uint32 Freq, uint8 OutEnable, PwmOutD_t *PwmOutD);
Status_t Pwm_Set_Duty_Cycle(uint8 Out, uint16 DutyCycle);
Status_t Pwm_Get_Duty_Cycle(uint8 Out, uint16 *DutyCycle);

#endif
