#include "main.h"
#include "lcd_12864.h"

void xuat_data(uint8_t data)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		switch (i)
		{
			case 0:
			{
				if(data & 0x01)DB0_on;
				else DB0_of;
			}
			break;
			case 1:
			{
				if(data & 0x02)DB1_on;
				else DB1_of;
			}
			break;
			case 2:
			{
				if(data & 0x04)DB2_on;
				else DB2_of;
			}
			break;
			case 3:
			{
				if(data & 0x08)DB3_on;
				else DB3_of;
			}
			break;
			case 4:
			{
				if(data & 0x10)DB4_on;
				else DB4_of;
			}
			break;
			case 5:
			{
				if(data & 0x20)DB5_on;
				else DB5_of;
			}
			break;
			case 6:
			{
				if(data & 0x40)DB6_on;
				else DB6_of;
			}
			break;
			case 7:
			{
				if(data & 0x80)DB7_on;
				else DB7_of;
			}
			break;
		}
	}
}

void write_data_lcd(unsigned char c)
{
	Delay_us(300);						// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY 
	LED_RS_on;
	LCD_RW_of;
	xuat_data(c);
	LCD_E_on;
	LCD_E_on;
	LCD_E_on;
	LCD_E_of;
}
// ==============================================================================
void write_command_lcd(unsigned char WCLCD,unsigned char BuysC) 
{
	if (BuysC) 
	Delay_us(200);						// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY
	LED_RS_of;
	LCD_RW_of;
	xuat_data(WCLCD);
	LCD_E_on;
	//LCD_E_on;
	//LCD_E_on;  
	Delay_us(10);
	LCD_E_of;
}

//===============================================================================
void lcd_Setaddress(unsigned char X, unsigned char Y)
{
	if(Y<1)
		Y=1;
	if(Y>4)
		Y=4;
	X &= 0x0F; 
	switch(Y)
	{
		case 1:X|=0X80;break;
		case 2:X|=0X90;break;
		case 3:X|=0X88;break;
		case 4:X|=0X98;break;
	}
	write_command_lcd(X, 0); 
}
// ==============================================================================
// HAM KHOI TAO LCD ------------------------------------------------
// MODE 8 bit ------------------------------------------------------
void lcd_init(void) 
{
// Function set
	write_command_lcd(0x30,1); 					// Chon che do truyen 8 bit
	Delay_us(150);											// delay > 100us
	write_command_lcd(0x30,1); 					// Chon che do truyen 8 bit
	Delay_us(50);												// delay > 37us
	// Display ON/OFF control
	write_command_lcd(0x0C,1); 					// Cho phep hien thi ra LCD 128x64
	Delay_us(120);											// delay > 100us
	
	// Clear LCD
	write_command_lcd(0x01,1); 					// Xoa man hinh			
	Delay_us(40);												// delay > 10ms
	// Entry mode set
	write_command_lcd(0x06,1); 					// Chon che do hien thi ki tu ra man hinh LCD 128x64 (Ki tu sau xuat hien ben phai ki tu truoc)
}
// ==============================================================================
void lcd_clear(void) 
{
	write_command_lcd(0x01,1);
	//write_command_lcd(0x34,1); 
	write_command_lcd(0x30,1); 
}
// ==============================================================================
void lcd_flash(void)	
{
	write_command_lcd(0x08,1);
	Delay_us(400);
	write_command_lcd(0x0c,1); 
	Delay_us(400);
	write_command_lcd(0x08,1); 
	Delay_us(400);
	write_command_lcd(0x0c,1); 
	Delay_us(400);
	write_command_lcd(0x08,1); 
	Delay_us(400);
}
// ==============================================================================
void lcd_putchar(unsigned char X, unsigned char Y, unsigned char DData)
{
	if(Y<1)
		Y=1;
	if(Y>4)
		Y=4;
	X &= 0x0F; 
	switch(Y)
	{
		case 1:X|=0X80;break;
		case 2:X|=0X90;break;
		case 3:X|=0X88;break;
		case 4:X|=0X98;break;
	}
	write_command_lcd(X, 0); 
	write_data_lcd(DData);
}
// ==============================================================================
void lcd_puts(unsigned char X, unsigned char Y, unsigned char *DData)
{
	unsigned char ListLength,X2;

	ListLength = 0;
	X2=X;
	if(Y<1)
		Y=1;
	if(Y>4)
		Y=4;
	X &= 0x0F; 
	switch(Y)
	{
		case 1:X2|=0X80;break;	
		case 2:X2|=0X90;break;
		case 3:X2|=0X88;break;
		case 4:X2|=0X98;break;
	}
	write_command_lcd(X2, 1); 
	while (DData[ListLength]>=0x20) 
	{
		if (X <= 0x0F) 
		{
			write_data_lcd(DData[ListLength]);
			ListLength++;
			X++;
			Delay_us(5);
		}
	}
}
// ==============================================================================
void lcd_display_image  (unsigned char *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;)
	{		
		for(x=0;x<32;x++)
		{				
			write_command_lcd(0x34,1);
			write_command_lcd((0x80+x),1);
			write_command_lcd((0x80+i),1);	
			write_command_lcd(0x30,1);		
			for(y=0;y<16;y++)	
				write_data_lcd(DData[tmp+y]);
			tmp+=16;		
		}
		i+=8;
	}
		write_command_lcd(0x36,1);	
		write_command_lcd(0x30,1);
}
// ==============================================================================
void delay_us_lcd(unsigned int time)
{
	uint32_t n;
	n=13*time;
	while(n--);
}
