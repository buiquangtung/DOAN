/**
  ******************************************************************************
  * @file    	lcd.h
  * @author  	ARMVN Application Team
  * @version 	V1.0.0
  * @date    	28/02/2010
  * @brief   	Header file for lcd.c module.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 ARMVietNam</center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_16X2_H
#define __LCD_16X2_H

#ifdef __cplusplus
 extern "C" {
#endif 

/*
*************************************************************************************************************************************
*															INCLUDED FILES															*
*************************************************************************************************************************************
*/
#include "stm32f10x.h"
// Dinh Nghia Cac Hang So
#define Line_1 0x80
#define Line_2 0xC0
	 
#define Clear_LCD 0x01
// Dinh nghia cac pin
#define LCD_RS_on  	GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define LCD_RS_off 	GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define LCD_RW_on  	GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define LCD_RW_off 	GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define LCD_EN_on  	GPIO_SetBits(GPIOA,GPIO_Pin_13)
#define LCD_EN_off 	GPIO_ResetBits(GPIOA,GPIO_Pin_13)

#define LCD_D4_on 	GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define LCD_D4_off 	GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define LCD_D5_on 	GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define LCD_D5_off 	GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define LCD_D6_on 	GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define LCD_D6_off 	GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define LCD_D7_on 	GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define LCD_D7_off 	GPIO_ResetBits(GPIOB,GPIO_Pin_5)

// void delay_us(__IO uint32_t us); // ham delay micro giay
// void delay_ms(__IO uint32_t ms); // ham delay mili giay
 void LCD_Enable(void);	//Tao xung Enable LCD
 void LCD_Send4Bit(unsigned char  Data);//Ham Gui 4 Bit Du Lieu Ra LCD
 void LCD_SendCommand (unsigned char command );// Ham Gui 1 Lenh Cho LCD
 void LCD_Init ( void );// Ham Khoi Tao LCD
 void LCD_GPIO_config(void);
 void LCD_Gotoxy(unsigned char x, unsigned char y);// Ham Thiet Lap Vi Tri Con Tro
 void LCD_Clear( void );// Ham Xoa Man Hinh LCD
 void LCD_PutChar (unsigned char Data );// Ham Gui 1 Ki Tu Len LCD
 void LCD_Puts (unsigned char *s);// Ham Gui 1 Chuoi Ki Tu Len LCD

#ifdef __cplusplus
}
#endif


#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2009 ARMVietNam *****END OF FILE****/
