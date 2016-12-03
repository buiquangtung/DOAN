/**
  ******************************************************************************
  * @file       main.h
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       28/02/2013
  ******************************************************************************
*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"
#include <stdio.h>
#include "i2c.h"
#include "24cxx.h"
#include "DEF_STM32.h"
	 
#define KEY_BUTTON_EXTI_LINE0  EXTI_Line0 

	 
#define OUT_IR_ON 			 GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define OUT_IR_OFF 			 GPIO_ResetBits(GPIOA,GPIO_Pin_1)
//#define SDA_on 			 GPIO_ResetBits(GPIOB,GPIO_Pin_5)
//#define SDA_off 		 GPIO_SetBits(GPIOB,GPIO_Pin_5)	 
//#define SCL_on  		 GPIO_ResetBits(GPIOB,GPIO_Pin_4)
//#define SCL_off 		 GPIO_SetBits(GPIOB,GPIO_Pin_4)
//#define LAT_on 			 GPIO_ResetBits(GPIOB,GPIO_Pin_3)
//#define LAT_off 		 GPIO_SetBits(GPIOB,GPIO_Pin_3)
	 
#define IN_BUTT_1	 	 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define IN_BUTT_2	 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define IN_BUTT_3	 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define IN_BUTT_4	 	 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define IN_BUTT_5	 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)

#define IN_BUTT_Mode_1	 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define IN_BUTT_Mode_2	 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define IN_BUTT_IR			 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
	 
#define SDA_on 			 GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define SDA_off 		 GPIO_ResetBits(GPIOB,GPIO_Pin_5)	 
#define SCL_on  		 GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define SCL_off 		 GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define LAT_on 			 GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define LAT_off 		 GPIO_ResetBits(GPIOB,GPIO_Pin_3)
/*________________________________ GPIO B ____________________________________*/
#define I2CSOFT_SDAOUT  PORTB_10
#define I2CSOFT_SDAIN   PINB_10
#define I2CSOFT_SCL     PORTB_11 


void RCC_Configuration(void);
void USART1_Configuration(void);
void _Delay_ms_mem(__IO uint32_t ms);
void _Delay_us_mem(__IO uint32_t us);
void Delay(__IO uint32_t num);
//void Delay_us(__IO uint32_t nTime);
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void get_clock(void);
void Timer2_init(void);
void Timer3_init(void);
void TIM1_Configuration(void);
void ext_line0_init(void);
void IO_config(void);
uint8_t BIT_BYTE(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7);
uint8_t NOT_BIT_BYTE(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7);
void CH_Timer_GPIO_Configuration(GPIO_TypeDef* GPIOx, int GPIO_Pin);
void PWM_timer_init(TIM_TypeDef* TIMx, int Period, int Prescaler);
void PWM_CH1(TIM_TypeDef* TIMx, uint16_t duty_cycle);
void PWM_CH2(TIM_TypeDef* TIMx, uint16_t duty_cycle);
void PWM_CH3(TIM_TypeDef* TIMx, uint16_t duty_cycle);
void PWM_CH4(TIM_TypeDef* TIMx, uint16_t duty_cycle);

void Out_data_IR(uint8_t * Data);
void BUTTON(void);

void View_data(uint8_t * data);
uint8_t Write_data(uint8_t byte,uint8_t * data);
#ifdef __GNUC__
	 
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/***
** @addtogroup STM32F10x_GEM3M_Examples.
  * @  Examples/Driver_Remap/main.h.
  * @  ARMPTIT NguyenVanThien Application. 
  * @  Header file for main.c module.
** @addtogroup STM32F10x_StdPeriph_Driver
***/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


/************************* linhkien69.vn ************************END OF FILE****/
