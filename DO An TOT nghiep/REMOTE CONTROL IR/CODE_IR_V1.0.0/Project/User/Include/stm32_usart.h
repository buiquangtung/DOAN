
/***
  ******************************************************************************
  * @file       stm32_usart.c
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       11/07/2015
  * @TomTa      Khai bao thu vien su dung
  *             Dinh nghia cac ham xu ly giao tiep USART voi MODULE SIM900a.
  *           
  *
  ******************************************************************************
  * Chu Y      :
  *                      
  ******************************************************************************
***/

#ifndef __STM32_USART_H
#define __STM32_USART_H      20150711													//		ma file		//


#include "main.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include <stdio.h>


/*------------------------------------------------------------------------------
  external functions
 *----------------------------------------------------------------------------*/
extern int  usart1_send_data(int ch);
extern int  usart1_get_data(void);
extern int  usart2_send_data(int ch);
extern int  usart2_get_data(void);
extern int  usart3_send_data(int ch);
extern int  usart3_get_data(void);

void usart_send_data(USART_TypeDef* USARTx, char data);

void usart1_init(GPIO_TypeDef* GPIO_x, int Pin_TX, int Pin_RX, long baudrate);
void usart2_init(GPIO_TypeDef* GPIO_x, int Pin_TX, int Pin_RX, long baudrate);
void usart3_init(GPIO_TypeDef* GPIO_x, int Pin_TX, int Pin_RX, long baudrate);

void usart1_send_string(const unsigned char* str);
void usart2_send_string(const char* str);
void usart3_send_string(const char* str);

void In_Config_ethernet(void);
unsigned char converter_int( unsigned char *data_conveter);

#endif

/*******************************************************************************
  -----   LINHKIEN69   ---- LINHKIEN69   ---- LINHKIEN69  ---- LINHKIEN69 ---
*******************************************************************************/



