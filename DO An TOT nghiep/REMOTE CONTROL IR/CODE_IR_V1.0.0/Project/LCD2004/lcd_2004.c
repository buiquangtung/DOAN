#include "main.h"
#include "lcd_2004.h"

uint8_t lcd_line; 

uint8_t const LCD_INIT_STRING[4] = 
{ 
 0x20 | (lcd_type << 2),  // Set mode: 4-bit, 2+ lines, 5x8 dots 
 0xc,                     // Display on 
 1,                       // Clear display 
 6                        // Increment cursor 
 }; 
                              

//------------------------------------- 
void lcd_send_nibble(uint8_t data) 
{ 
// Note:  !! converts an integer expression 
// to a boolean (1 or 0). 
	uint8_t i;
	for(i=0;i<8;i++)
	{
		switch (i)
		{
			case 0:
			{
				if(data & 0x01)DB4_on;
				else DB4_of;
			}
			break;
			case 1:
			{
				if(data & 0x02)DB5_on;
				else DB5_of;
			}
			break;
			case 2:
			{
				if(data & 0x04)DB6_on;
				else DB6_of;
			}
			break;
			case 3:
			{
				if(data & 0x08)DB7_on;
				else DB7_of;
			}
			break;
		}
	}
/*output_bit(LCD_DB4, nibble & 1); 
output_bit(LCD_DB5, nibble & 2);  
output_bit(LCD_DB6, nibble & 4);    
output_bit(LCD_DB7, nibble & 8);    
*/
 _Delay_us_mem(1); 
 LCD_E_on;														//output_high(LCD_E); 
 _Delay_us_mem(2); 
 LCD_E_of;													//output_low(LCD_E); 
} 

//----------------------------------- 
// This sub-routine is only called by lcd_read_byte(). 
// It's not a stand-alone routine.  For example, the 
// R/W signal is set high by lcd_read_byte() before 
// this routine is called.      

#ifdef USE_RW_PIN 
uint8_t lcd_read_nibble(void) 
{ 
uint8_t retval; 
// Create bit variables so that we can easily set 
// individual bits in the retval variable. 
//#bit retval_0 = retval.0 
//#bit retval_1 = retval.1 
//#bit retval_2 = retval.2 
//#bit retval_3 = retval.3 

retval = 0; 
    
LCD_E_on;																		//output_high(LCD_E); 
_Delay_us_mem(1); 
config_input_lcd();
//retval_0 = input(LCD_DB4); 
//retval_1 = input(LCD_DB5); 
//retval_2 = input(LCD_DB6); 
//retval_3 = input(LCD_DB7); 
retval = retval|input_DB7;
retval = retval<<1;
retval = retval|input_DB6;
retval = retval<<1;
retval = retval|input_DB5;
retval = retval<<1;
retval = retval|input_DB4;
LCD_E_of;  //output_low(LCD_E); 
config_output_lcd();
_Delay_us_mem(1); 
    
return(retval);    
}    
#endif 

//--------------------------------------- 
// Read a byte from the LCD and return it. 

#ifdef USE_RW_PIN 
uint8_t lcd_read_byte(void) 
{ 
uint8_t low; 
uint8_t high; 

LCD_RW_on; //output_high(LCD_RW); 
_Delay_us_mem(1); 

high = lcd_read_nibble(); 

low = lcd_read_nibble(); 

return( (high<<4) | low); 
} 
#endif 
uint8_t lcd_bit_test(uint8_t bit)
{
 uint8_t data_valu;
 data_valu = lcd_read_byte();
 data_valu = (data_valu & (1<<bit));
 return(data_valu);
}
//---------------------------------------- 
// Send a byte to the LCD. 
void lcd_send_byte(uint8_t address, uint8_t n) 
{ 
LCD_RS_of;//output_low(LCD_RS); 

#ifdef USE_RW_PIN 
//while(bit_test(lcd_read_byte(),7)) ; 
while(lcd_bit_test(7)) ; 
#else 
delay_us(60);  
#endif 

if(address) 
{
	LCD_RS_on;	//output_high(LCD_RS); 
}
else 
{
	LCD_RS_of;  //output_low(LCD_RS); 
}
      
 _Delay_us_mem(1); 

#ifdef USE_RW_PIN 
LCD_RW_of;  //output_low(LCD_RW); 
_Delay_us_mem(1); 
#endif 
LCD_E_of;  //output_low(LCD_E); 

lcd_send_nibble(n >> 4); 
lcd_send_nibble(n & 0xf); 
} 
//---------------------------- 
void lcd_Clear(void)
{
	printf("\f");
}
void lcd_init(void) 
{ 
uint8_t i; 

lcd_line = 1; 

LCD_RS_of; //output_low(LCD_RS); 

#ifdef USE_RW_PIN 
LCD_RW_of; //output_low(LCD_RW); 
#endif 
LCD_E_of;  //output_low(LCD_E); 
// Some LCDs require 15 ms minimum delay after 
// power-up.  Others require 30 ms.  I'm going 
// to set it to 35 ms, so it should work with 
// all of them. 
_Delay_ms_mem(35);          

for(i=0 ;i < 3; i++) 
   { 
    lcd_send_nibble(0x03); 
    _Delay_ms_mem(5); 
   } 

lcd_send_nibble(0x02); 

for(i=0; i < sizeof(LCD_INIT_STRING); i++) 
   { 
    lcd_send_byte(0, LCD_INIT_STRING[i]); 
    
    // If the R/W signal is not used, then 
    // the busy bit can't be polled.  One of 
    // the init commands takes longer than 
    // the hard-coded delay of 50 us, so in 
    // that case, lets just do a 5 ms delay 
    // after all four of them. 
    #ifndef USE_RW_PIN 
    delay_ms(5); 
    #endif 
   } 

} 

//---------------------------- 

void lcd_gotoxy(uint8_t x, uint8_t y) 
{ 
uint8_t address; 


switch(y) 
  { 
   case 1: 
     address = LCD_LINE_1_ADDRESS; 
     break; 

   case 2: 
     address = LCD_LINE_2_ADDRESS; 
     break; 

   case 3: 
     address = LCD_LINE_3_ADDRESS; 
     break; 

   case 4: 
     address = LCD_LINE_4_ADDRESS; 
     break; 

   default: 
     address = LCD_LINE_1_ADDRESS; 
     break; 
      
  } 

address += x-1; 
lcd_send_byte(0, 0x80 | address); 
} 

//----------------------------- 
void lcd_putc(char c) 
{ 
 switch(c) 
   { 
    case '\f': 
      lcd_send_byte(0,1); 
      lcd_line = 1; 
      _Delay_ms_mem(2); 
      break; 
    
    case '\n': 
       lcd_gotoxy(1, ++lcd_line); 
       break; 
    
    case '\b': 
       lcd_send_byte(0,0x10); 
       break; 
    
    default: 
       lcd_send_byte(1,c); 
       break; 
   } 
} 

//------------------------------ 
#ifdef USE_RW_PIN 
char lcd_getc(uint8_t x, uint8_t y)
{ 
char value; 

lcd_gotoxy(x,y); 

// Wait until busy flag is low. 
//while(bit_test(lcd_read_byte(),7));  
while(lcd_bit_test(7)) ; 
LCD_RS_on; //output_high(LCD_RS); 
value = lcd_read_byte(); 
LCD_RS_of; //output_low(LCD_RS); 

return(value); 
} 
void config_input_lcd(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void config_output_lcd(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}
#endif 
void delay_us_lcd(unsigned int time)
{
	uint32_t n;
	n=13*time;
	while(n--);
}
