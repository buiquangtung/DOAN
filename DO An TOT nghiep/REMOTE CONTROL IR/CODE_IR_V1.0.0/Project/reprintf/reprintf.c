#include <stdio.h>
#include "reprintf.h"
#include "stm32f10x_usart.h"
#include "lcd_16x2.h"

extern int8_t target;

PUTCHAR_PROTOTYPE
{
   /* Place your implementation of fputc here */
     /* e.g. write a character to the LCD */
   if ( target )LCD_PutChar((char) ch);    //lcd_Data_Write((u8)ch);
   else 
   {
   USART_SendData(USART1, (uint8_t) ch);

   /* Loop until the end of transmission */
   while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
   {}
   }
     return ch;
}

/*********************************END OF FILE****/
