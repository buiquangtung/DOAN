#include "lcd_16x2.h"
#include "main.h"
//Tao Xung
 void LCD_Enable(void)
{
 LCD_EN_on;
 _Delay_us_mem(3);
 LCD_EN_off;
 _Delay_us_mem(50); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD
 void LCD_Send4Bit( unsigned char Data )
{
	unsigned int i;
	for(i=0;i<=3;i++)
	{
	switch (i)
	{
		case 0:
		{
			if(Data & 0x01) LCD_D4_on;
			else LCD_D4_off;
		}
		break;
		case 1:
		{
			if((Data>>1)&1) LCD_D5_on;
			else LCD_D5_off;
		}
		break;
		case 2:
		{
			if((Data>>2)&1) LCD_D6_on;
			else LCD_D6_off;
		}
		break;
		case 3:
		{
			if((Data>>3)&1) LCD_D7_on;
			else LCD_D7_off;
		}
		break;
	}
	}
}
// Ham Gui 1 Lenh Cho LCD
 void LCD_SendCommand (unsigned char command )
{
LCD_Send4Bit  ( command >>4 );/* Gui 4 bit cao */
LCD_Enable () ;
LCD_Send4Bit  ( command  );		/* Gui 4 bit thap*/
LCD_Enable () ;
}
// Ham Khoi Tao LCD
 void LCD_Init ( void )
{
LCD_GPIO_config();
_Delay_ms_mem(20);
LCD_Send4Bit(0x00);
_Delay_ms_mem(20);
LCD_RS_off;
LCD_RW_off;
LCD_Send4Bit(0x03);
LCD_Enable();
_Delay_ms_mem(5);
LCD_Enable();
_Delay_us_mem(100);
LCD_Enable();
LCD_Send4Bit(0x02);
LCD_Enable();
LCD_SendCommand( 0x28 );      // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
LCD_SendCommand( 0x0c); 	    // cho phep hien thi man hinh
LCD_SendCommand( 0x06 );      // tang ID, khong dich khung hinh
LCD_SendCommand( Clear_LCD ); // xoa toan bo khung hinh
}
void LCD_Gotoxy(unsigned char x, unsigned char y)
{
  unsigned char address;
  if(!y)
  address = (Line_1+x);
  else
  address = (Line_2+x);
  _Delay_us_mem(1000);
  LCD_SendCommand(address);
  _Delay_us_mem(50);
}
// Ham Xoa Man Hinh LCD
void LCD_Clear( void )
{
  LCD_SendCommand( Clear_LCD );  
  _Delay_ms_mem(5);
}
// Ham Gui 1 Ki Tu Len LCD
 void LCD_PutChar (unsigned char Data )
{
 LCD_RS_on;
 LCD_SendCommand( Data );
 LCD_RS_off;
}
void LCD_Puts (unsigned char *s)
{
   while (*s)
   {
      LCD_PutChar(*s);
      s++;
   }
}
void LCD_GPIO_config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	                                                        
		GPIO_InitStructure.GPIO_Pin   = (GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15);
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin   = (GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

