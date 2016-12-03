#ifndef __LCD_12864_H
#define __LCD_12864_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_gpio.h"
	 
#define Busy    0x80 

#define PSB_on       GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define PSB_of       GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define LED_RS_on 	 GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define LED_RS_of 	 GPIO_ResetBits(GPIOB,GPIO_Pin_12)   //RS
#define LCD_RW_on		 GPIO_SetBits(GPIOB,GPIO_Pin_13)//data R/W
#define LCD_RW_of 	 GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define LCD_E_on 		 GPIO_SetBits(GPIOB,GPIO_Pin_14)//clock E
#define LCD_E_of 		 GPIO_ResetBits(GPIOB,GPIO_Pin_14)
//#define LCD_REST_on  GPIO_WriteHigh(GPIOB,GPIO_Pin_10)//REST
//#define LCD_REST_of  GPIO_WriteLow(GPIOB,GPIO_Pin_10)
///////////////////////////////////////////////////////DATA LCD
#define DB0_on    GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define DB0_of    GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define DB1_on    GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define DB1_of    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define DB2_on    GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define DB2_of    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define DB3_on    GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define DB3_of    GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define DB4_on    GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define DB4_of    GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define DB5_on    GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define DB5_of    GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define DB6_on    GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define DB6_of    GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define DB7_on    GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define DB7_of    GPIO_ResetBits(GPIOA,GPIO_Pin_7)
void delay_us_lcd(uint32_t time);
//void delay_ms_lcd(unsigned int time);
//void Delay_nms_lcd(unsigned char n);
void config_GPIO_LCD(void);
void xuat_data(unsigned char data );
// Ham cho phep viet 1 byte du lieu vao LCD ---------------------------------------
void write_data_lcd( unsigned char c);	

// Ham cho phep viet 1 byte lenh dieu khien vao LCD -------------------------------
void write_command_lcd(unsigned char WCLCD,unsigned char BuysC);

// Ham cho phep khoi tao de su dung  LCD ------------------------------------------
void lcd_init(void);

// Ham cho phep xoa toan bo man hinh LCD ------------------------------------------
void lcd_clear(void);

// Ham cho phep ON/OFF hien thi ra man hinh LCD -----------------------------------
void lcd_flash(void);

// Ham cho phep viet 1 ki tu ra man hinh LCD --------------------------------------
void lcd_putchar(unsigned char X, unsigned char Y, unsigned char DData);

// Ham cho phep viet 1 chuoi ki tu ra man hinh LCD --------------------------------
void lcd_puts(unsigned char X, unsigned char Y, unsigned char *DData);

// Ham cho phep hien thi hinh anh ra man hinh LCD ----------------------------------
void lcd_display_image (unsigned char *DData);

// -------------------------------------------------------------------
void lcd_Setaddress(unsigned char X, unsigned char Y);

//unsigned char read_data_lcd(void);



#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */


/******************* (C)____Nguyen manh cuong_linhken69.VN_____*****END OF FILE****/


