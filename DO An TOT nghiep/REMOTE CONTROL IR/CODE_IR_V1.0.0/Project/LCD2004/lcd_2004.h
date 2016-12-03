#ifndef __LCD_2004_H
#define __LCD_2004_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_gpio.h"

#define USE_RW_PIN   1      
// These are the line addresses for most 4x20 LCDs. 
#define LCD_LINE_1_ADDRESS 0x00 
#define LCD_LINE_2_ADDRESS 0x40 
#define LCD_LINE_3_ADDRESS 0x14 
#define LCD_LINE_4_ADDRESS 0x54 

// These are the line addresses for LCD's which use 
// the Hitachi HD66712U controller chip. 

//======================================== 

#define lcd_type 2   // 0=5x7, 1=5x10, 2=2 lines(or more) 


#define LCD_RS_on 	 GPIO_SetBits  (GPIOB,GPIO_Pin_3)
#define LCD_RS_of 	 GPIO_ResetBits(GPIOB,GPIO_Pin_3)   //RS
#define LCD_RW_on		 GPIO_SetBits  (GPIOB,GPIO_Pin_4)//data R/W
#define LCD_RW_of 	 GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define LCD_E_on 		 GPIO_SetBits  (GPIOB,GPIO_Pin_5)//clock E
#define LCD_E_of 		 GPIO_ResetBits(GPIOB,GPIO_Pin_5)
//////////////////////////////////////////////////////////////////
#define DB4_on    GPIO_SetBits	(GPIOB,GPIO_Pin_6)
#define DB4_of    GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define DB5_on    GPIO_SetBits	(GPIOB,GPIO_Pin_7)
#define DB5_of    GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define DB6_on    GPIO_SetBits	(GPIOB,GPIO_Pin_8)
#define DB6_of    GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define DB7_on    GPIO_SetBits	(GPIOB,GPIO_Pin_9)
#define DB7_of    GPIO_ResetBits(GPIOB,GPIO_Pin_9)
/////////////////////////////////////////////////////////////////
#define input_DB4     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6);
#define input_DB5			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);
#define input_DB6			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
#define input_DB7			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
/////////////////////////////////////////////////////////////////
void lcd_send_nibble(uint8_t data) ;
uint8_t lcd_read_nibble(void);
uint8_t lcd_read_byte(void);
uint8_t lcd_bit_test(uint8_t bit);
void lcd_send_byte(uint8_t address, uint8_t n);
void lcd_Clear(void);
void lcd_init(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_putc(char c);
char lcd_getc(uint8_t x, uint8_t y);
void config_input_lcd(void);
void config_output_lcd(void);
void delay_us_lcd(unsigned int time);
//////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */


/******************* (C)____Nguyen manh cuong_linhken69.VN_____*****END OF FILE****/


