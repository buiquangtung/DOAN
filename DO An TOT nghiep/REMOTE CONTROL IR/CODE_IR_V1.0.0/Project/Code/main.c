/**
  ******************************************************************************
  * @file       main.c
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       28/02/2013
  ******************************************************************************
*/

#include "main.h"
#include "lcd_16x2.h"

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
static __IO uint32_t TimingDelay;
uint32_t clk_freq;
uint8_t target=0,i,ii,j,set_led;
uint32_t T_IR_out;
uint8_t Butt_Data_IR[32];
uint8_t Butt_1_Data_mode1[4],Butt_2_Data_mode1[4],Butt_3_Data_mode1[4],Butt_4_Data_mode1[4],Butt_5_Data_mode1[4];
uint8_t Butt_1_Data_mode2[4],Butt_2_Data_mode2[4],Butt_3_Data_mode2[4],Butt_4_Data_mode2[4],Butt_5_Data_mode2[4];

uint8_t Get_data;

uint8_t star_ok=0,ok_Data=0;

uint8_t ID_data_BT1_Mode1=0,ID_data_BT2_Mode1=4,ID_data_BT3_Mode1=8,ID_data_BT4_Mode1=12,ID_data_BT5_Mode1=16;
uint8_t ID_data_BT1_Mode2=20,ID_data_BT2_Mode2=24,ID_data_BT3_Mode2=28,ID_data_BT4_Mode2=32,ID_data_BT5_Mode2=36;

uint8_t fast_Butt_1,fast_Butt_2,fast_Butt_3,fast_Butt_4,fast_Butt_5,fast_Butt_mode=0,fast_Butt_ir;

int main(void)
{ 
	/* Configure the system clocks */
	RCC_Configuration();
	IO_config();
	USART1_Configuration();
	Timer2_init();
	Timer3_init();
	TIM1_Configuration();
	ext_line0_init();
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 		
		/* Capture error */ 
		while (1){}
	}
	_Delay_ms_mem(1000);				// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY (>40ms)
	get_clock();
	I2CSOFT_Init();
	printf("clock SysTick = %3u\n",clk_freq);
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE);
	LCD_Init();
	OUT_IR_OFF;
	TIM_Cmd(TIM3, ENABLE);
	target=0;
	CH_Timer_GPIO_Configuration(GPIOB, GPIO_Pin_6);
  PWM_timer_init(TIM4, 1894, 1);
	PWM_CH1(TIM4,1894);
	target=0;
	EEP24CXX_ReadMultiData(ID_data_BT1_Mode1,4,Butt_1_Data_mode1);
	EEP24CXX_ReadMultiData(ID_data_BT2_Mode1,4,Butt_2_Data_mode1);
	EEP24CXX_ReadMultiData(ID_data_BT3_Mode1,4,Butt_3_Data_mode1);
	EEP24CXX_ReadMultiData(ID_data_BT4_Mode1,4,Butt_4_Data_mode1);
	EEP24CXX_ReadMultiData(ID_data_BT5_Mode1,4,Butt_5_Data_mode1);
	
	EEP24CXX_ReadMultiData(ID_data_BT1_Mode2,4,Butt_1_Data_mode2);
	EEP24CXX_ReadMultiData(ID_data_BT2_Mode2,4,Butt_2_Data_mode2);
	EEP24CXX_ReadMultiData(ID_data_BT3_Mode2,4,Butt_3_Data_mode2);
	EEP24CXX_ReadMultiData(ID_data_BT4_Mode2,4,Butt_4_Data_mode2);
	EEP24CXX_ReadMultiData(ID_data_BT5_Mode2,4,Butt_5_Data_mode2);
	View_data(Butt_1_Data_mode1);
	target=1;
	LCD_Gotoxy(0,0);
	printf(" MODE_1 ");
	
	while (1)	
	{
		BUTTON();
		if(fast_Butt_ir==1)
		{
			if(fast_Butt_mode==0)
			{
				if(fast_Butt_1==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode1_T1");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_1_Data_mode1[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_1_Data_mode1);
						EEP24CXX_WriteMultiData(ID_data_BT1_Mode1,4,Butt_1_Data_mode1);
					}
				}
				else if(fast_Butt_2==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode1_T2");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_2_Data_mode1[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_2_Data_mode1);
						EEP24CXX_WriteMultiData(ID_data_BT2_Mode1,4,Butt_2_Data_mode1);
					}
				}
				else if(fast_Butt_3==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode1_T3");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_3_Data_mode1[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_3_Data_mode1);
						EEP24CXX_WriteMultiData(ID_data_BT3_Mode1,4,Butt_3_Data_mode1);
					}
				}
				else if(fast_Butt_4==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode1_T4");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_4_Data_mode1[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_4_Data_mode1);
						EEP24CXX_WriteMultiData(ID_data_BT4_Mode1,4,Butt_4_Data_mode1);
					}
				}
				else if(fast_Butt_5==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode1_T5");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_5_Data_mode1[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_5_Data_mode1);
						EEP24CXX_WriteMultiData(ID_data_BT5_Mode1,4,Butt_5_Data_mode1);
					}
				}
			}
			else
			{
				if(fast_Butt_1==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode2_T1");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_1_Data_mode2[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_1_Data_mode2);
						EEP24CXX_WriteMultiData(ID_data_BT1_Mode2,4,Butt_1_Data_mode2);
					}
				}
				else if(fast_Butt_2==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode2_T2");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_2_Data_mode2[i]=Write_data(i,Butt_Data_IR);////
						}
						View_data(Butt_2_Data_mode2);///
						EEP24CXX_WriteMultiData(ID_data_BT2_Mode2,4,Butt_2_Data_mode2);////
					}
				}
				else if(fast_Butt_3==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode2_T3");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_3_Data_mode2[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_3_Data_mode2);
						EEP24CXX_WriteMultiData(ID_data_BT3_Mode2,4,Butt_3_Data_mode2);
					}
				}
				else if(fast_Butt_4==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode2_T4");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_4_Data_mode2[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_4_Data_mode2);
						EEP24CXX_WriteMultiData(ID_data_BT4_Mode2,4,Butt_4_Data_mode2);
					}
				}
				else if(fast_Butt_5==1)
				{
					target=1;
					LCD_Gotoxy(0,0);
					printf("Mode2_T5");
					if(Get_data==1)
					{
						Get_data=0;
						for(i=0;i<4;i++)
						{
							Butt_5_Data_mode2[i]=Write_data(i,Butt_Data_IR);
						}
						View_data(Butt_5_Data_mode2);
						EEP24CXX_WriteMultiData(ID_data_BT5_Mode2,4,Butt_5_Data_mode2);
					}
				}
			}
		}
		else
		{
			if(fast_Butt_mode==0)
			{
				if(fast_Butt_1==1)
				{
					fast_Butt_1=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_1 ");
					View_data(Butt_1_Data_mode1);
					Out_data_IR(Butt_1_Data_mode1);
				}
				else if(fast_Butt_2==1)
				{
					fast_Butt_2=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_1 ");
					View_data(Butt_2_Data_mode1);
					Out_data_IR(Butt_2_Data_mode1);
				}
				else if(fast_Butt_3==1)
				{
					fast_Butt_3=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_1 ");
					View_data(Butt_3_Data_mode1);
					Out_data_IR(Butt_3_Data_mode1);
				}
				else if(fast_Butt_4==1)
				{
					fast_Butt_4=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_1 ");
					View_data(Butt_4_Data_mode1);
					Out_data_IR(Butt_4_Data_mode1);
				}
				else if(fast_Butt_5==1)
				{
					fast_Butt_5=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_1 ");
					View_data(Butt_5_Data_mode1);
					Out_data_IR(Butt_5_Data_mode1);
				}
			}
			else
			{
				if(fast_Butt_1==1)
				{
					fast_Butt_1=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_2 ");
					View_data(Butt_1_Data_mode2);
					Out_data_IR(Butt_1_Data_mode2);
				}
				else if(fast_Butt_2==1)
				{
					fast_Butt_2=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_2 ");
					View_data(Butt_2_Data_mode2);
					Out_data_IR(Butt_2_Data_mode2);
				}
				else if(fast_Butt_3==1)
				{
					fast_Butt_3=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_2 ");
					View_data(Butt_3_Data_mode2);
					Out_data_IR(Butt_3_Data_mode2);
				}
				else if(fast_Butt_4==1)
				{
					fast_Butt_4=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_2 ");
					View_data(Butt_4_Data_mode2);
					Out_data_IR(Butt_4_Data_mode2);
				}
				else if(fast_Butt_5==1)
				{
					fast_Butt_5=0;
					target=1;
					LCD_Gotoxy(0,0);
					printf(" MODE_2 ");
					View_data(Butt_5_Data_mode2);
					Out_data_IR(Butt_5_Data_mode2);
				}
			}
		}
	}
}
uint8_t Write_data(uint8_t byte,uint8_t * data)
{
	uint8_t byte_data;
	if     (byte==0) byte_data = BIT_BYTE(data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
	else if(byte==1) byte_data = BIT_BYTE(data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15]);
	else if(byte==2) byte_data = BIT_BYTE(data[16],data[17],data[18],data[19],data[20],data[21],data[22],data[23]);
	else if(byte==3) byte_data = BIT_BYTE(data[24],data[25],data[26],data[27],data[28],data[29],data[30],data[31]);
	return byte_data;
}
void BUTTON(void)
{
	static uint8_t quet_button,button_1,button_2,button_3,button_4,button_5,button_Mode_1,button_Mode_2,button_IR;
	quet_button++;
	if(quet_button>2)
	{
		quet_button=0;
		if(!IN_BUTT_1)button_1++;
		else button_1=0;
		if(button_1==4)
		{
			fast_Butt_1=1;
			fast_Butt_2=0;
			fast_Butt_3=0;
			fast_Butt_4=0;
			fast_Butt_5=0;
		}
		if(button_1==10)button_1=5;
		//////////////////////////////////////
		if(!IN_BUTT_2)button_2++;
		else button_2=0;
		if(button_2==4)
		{
			fast_Butt_2=1;
			fast_Butt_1=0;
			fast_Butt_3=0;
			fast_Butt_4=0;
			fast_Butt_5=0;
		}
		if(button_2==10)button_2=5;
		//////////////////////////////////////
		if(!IN_BUTT_3)button_3++;
		else button_3=0;
		if(button_3==4)
		{
			fast_Butt_3=1;
			fast_Butt_1=0;
			fast_Butt_2=0;
			fast_Butt_4=0;
			fast_Butt_5=0;
		}
		if(button_3==10)button_3=5;
		//////////////////////////////////////
		if(!IN_BUTT_4)button_4++;
		else button_4=0;
		if(button_4==4)
		{
			fast_Butt_4=1;
			fast_Butt_1=0;
			fast_Butt_2=0;
			fast_Butt_3=0;
			fast_Butt_5=0;
		}
		if(button_4==10)button_4=5;
		//////////////////////////////////////
		if(!IN_BUTT_5)button_5++;
		else button_5=0;
		if(button_5==4)
		{
			fast_Butt_5=1;
			fast_Butt_1=0;
			fast_Butt_2=0;
			fast_Butt_3=0;
			fast_Butt_4=0;
		}
		if(button_5==10)button_5=5;
		//////////////////////////////////////
		if(!IN_BUTT_Mode_1)button_Mode_1++;
		else button_Mode_1=0;
		if(button_Mode_1==4)
		{
			fast_Butt_mode=0;
			if(fast_Butt_ir==0)
			{
				target=1;
				LCD_Gotoxy(0,0);
				printf(" MODE_1 ");
				LCD_Gotoxy(0,1);
				printf("        ");
			}
		}
		if(button_Mode_1==10)button_Mode_1=5;
		//////////////////////////////////////
		if(!IN_BUTT_Mode_2)button_Mode_2++;
		else button_Mode_2=0;
		if(button_Mode_2==4)
		{
			fast_Butt_mode=1;
			if(fast_Butt_ir==0)
			{
				target=1;
				LCD_Gotoxy(0,0);
				printf(" MODE_2 ");
				LCD_Gotoxy(0,1);
				printf("        ");
			}
		}
		if(button_Mode_2==10)button_Mode_2=5;
		//////////////////////////////////////
		if(!IN_BUTT_IR)button_IR++;
		else button_IR=0;
		if(button_IR==4)
		{
			if(fast_Butt_ir==0)
			{
				fast_Butt_ir=1;
				target=1;
				LCD_Gotoxy(0,0);
				printf(" Get_IR ");
				LCD_Gotoxy(0,1);
				printf("        ");
				Delay_ms(500);
			}
			else 
			{
				fast_Butt_ir=0;
				fast_Butt_1=0;
				fast_Butt_2=0;
				fast_Butt_3=0;
				fast_Butt_4=0;
				fast_Butt_5=0;
				target=1;
				LCD_Gotoxy(0,0);
				if(fast_Butt_mode==0)
				{
					printf(" MODE_1 ");
					LCD_Gotoxy(0,1);
					printf("        ");
					Delay_ms(500);
				}
				else 
				{
					printf(" MODE_2 ");
					LCD_Gotoxy(0,1);
					printf("        ");
					Delay_ms(500);
				}
			}
		}
		if(button_IR==10)button_IR=5;
		//////////////////////////////////////
	}
}
void View_data(uint8_t * data)
{
	uint32_t DATA_IR;
	
	DATA_IR=data[0];
	DATA_IR=DATA_IR<<8;
	DATA_IR=DATA_IR|data[1];
	DATA_IR=DATA_IR<<8;
	DATA_IR=DATA_IR|data[2];
	DATA_IR=DATA_IR<<8;
	DATA_IR=DATA_IR|data[3];
	
	target=0;
	for(i=0;i<4;i++)
	{
		printf("%X|",data[i]);
	}
	printf("\r\n");
	target=1;
	LCD_Gotoxy(0,1);
	printf("%8.X   ",DATA_IR);
	
}
void Out_data_IR(uint8_t * Data_byte)
{
	uint8_t Data[32];
	uint8_t kk,byte_0,byte_1,byte_2,byte_3;
	
	byte_0=Data_byte[0];
	byte_1=Data_byte[1];
	byte_2=Data_byte[2];
	byte_3=Data_byte[3];
	
	for(kk=0;kk<8;kk++)
	{
		if(byte_0&0x01)Data[kk]=1;
		else Data[kk]=0;
		byte_0>>=1;
	}
	for(kk=0;kk<8;kk++)
	{
		if(byte_1&0x01)Data[kk+8]=1;
		else Data[kk+8]=0;
		byte_1>>=1;
	}
	for(kk=0;kk<8;kk++)
	{
		if(byte_2&0x01)Data[kk+16]=1;
		else Data[kk+16]=0;
		byte_2>>=1;
	}
	for(kk=0;kk<8;kk++)
	{
		if(byte_3&0x01)Data[kk+24]=1;
		else Data[kk+24]=0;
		byte_3>>=1;
	}
	target=0;
	for(i=0;i<32;i++)
	{
		printf("%d",Data[i]);
	}
	printf("\r\n");
	printf("data\r\n");
	/////////////////////////
	TIM_SetCounter(TIM3,0);
	T_IR_out=0;
	PWM_CH1(TIM4,947);///on
	while(T_IR_out<=9000)
	{
		T_IR_out = TIM_GetCounter(TIM3);
	}
	PWM_CH1(TIM4,1895);///of
	TIM_SetCounter(TIM3,0);
	T_IR_out=0;
	while(T_IR_out<=4500)
	{
		T_IR_out = TIM_GetCounter(TIM3);
	}
	PWM_CH1(TIM4,947);///on
	for(i=0;i<32;i++)
	{
		if(Data[i]==1)////////////1
		{
			PWM_CH1(TIM4,947);///on
			TIM_SetCounter(TIM3,0);
			T_IR_out=0;
			while(T_IR_out<=560)
			{
				T_IR_out = TIM_GetCounter(TIM3);
			}
			PWM_CH1(TIM4,1895);///of
			TIM_SetCounter(TIM3,0);
			T_IR_out=0;
			while(T_IR_out<=1690)
			{
				T_IR_out = TIM_GetCounter(TIM3);
			}
			PWM_CH1(TIM4,947);///on
		}
		else///////////0
		{
			PWM_CH1(TIM4,947);///on
			TIM_SetCounter(TIM3,0);
			T_IR_out=0;
			while(T_IR_out<=560)
			{
				T_IR_out = TIM_GetCounter(TIM3);
			}
			PWM_CH1(TIM4,1895);///of
			TIM_SetCounter(TIM3,0);
			T_IR_out=0;
			while(T_IR_out<=560)
			{
				T_IR_out = TIM_GetCounter(TIM3);
			}
			PWM_CH1(TIM4,947);///on
		}
	}
	Delay_ms(10);
	PWM_CH1(TIM4,1895);///of
}
/*******************************************************************************
Noi Dung    :   Ham ghep 8 bit du lieu nhan duoc thanh 1 Byte hoan chinh
Tham Bien   :   D0, D1, D2, D3, D4, D5, D6, D7.
Tra Ve      :   Byte du lieu
********************************************************************************/ 
uint8_t BIT_BYTE(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7)
{
   uint8_t data; 
   data= D7*128 + D6*64 + D5*32 + D4*16 + D3*8 + D2*4 + D1*2 +D0*1; // 0 den 255 
   return data; 
}
uint8_t NOT_BIT_BYTE(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7)
{
   uint8_t data; 
   data= (!D7)*128 + (!D6)*64 + (!D5)*32 + (!D4)*16 + (!D3)*8 + (!D2)*4 + (!D1)*2 +(!D0)*1; // 0 den 255 
   return data; 
}

void ext_line0_init(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		  // chon ngat tren chan PA0
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  // Chon la Input pull Down
  	GPIO_Init(GPIOA, &GPIO_InitStructure);  		  // Port A
	
  	/* SEL Button */
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);		   // Chon Line_0 cua ngat ngoai

	/* Clear the the EXTI line 0 interrupt pending bit */
	// Khoi tao cac che do cho ngat

		EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE0);

		EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;	   // Chon che do ngat
		EXTI_InitStructure.EXTI_Line 		= KEY_BUTTON_EXTI_LINE0;	   // Ngat tai Line_0
		EXTI_InitStructure.EXTI_Trigger 	= EXTI_Trigger_Falling;	   // tai suon duong cua xung Clock thi ngat xay ra
		EXTI_InitStructure.EXTI_LineCmd 	= ENABLE;				   
		EXTI_Init(&EXTI_InitStructure);

	/* Enable the EXTI0 Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			   // Khoi tao ngat tai Line_0
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;	   // ???
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   // Uu tien ngat
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure); 
}
void Timer2_init(void)
{
	
		NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* Khoi tao timer 2 thanh ngat 1 ms */

	 /* Enable the TIM2 gloabal Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel                      = TIM2_IRQn;	 // Khoi tao vecto ngat timer4
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 1;			 // Muc uu tien cua ngat
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;		 // Cho phep ngat

  	NVIC_Init(&NVIC_InitStructure);

  	/* TIM2 clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 // Enable Clock Timer2 on APB1 with frequency 36Mhz

/* ---------------------------------------------------------------------------//
    APB1 prescaler = 1 = 1 => PCLK2 = HCLK/1 => 72MHz/1 = 72MHz => 
 
    TIM1CLK = PCLK2 x 1 = 72 MHz, Prescaler = 71 => TIM2 counter clock = TIM2CLK /( Prescaler + 1 ) = 1 MHz
 
    TIM2 ARR Register = 65535 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
 
    / Time base configuration */
 
    TIM_TimeBaseStructure.TIM_Period = 65535;
 
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
 
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	
		  	/* TIM IT enable */
  	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  	/* TIM2 enable counter */
  	//TIM_Cmd(TIM2, ENABLE);						  // Bat timer2
		TIM_Cmd(TIM2, DISABLE);
}
/****************************************************************************

	Ham cau hinh cac kenh cua bo Timer:
	Timer1 :				Timer2 : 			Timer3 : 			Timer4 :
	CH1 : PA8				CH1 : PA0 		CH1 : PA6			CH1 : PB6
	CH2 : PA9				CH2 : PA1			CH2 : PA7			CH2 :	PB7
	CH3 : PA10			CH3 : PA2			CH3 : PB0			CH3 : PB8
	CH4 : PA11 			CH4 : PA3			CH4 : PB1			CH4 : PB9
	
	voi GPIO_Pin = GPIO_Pin_x|GPIO_Pin_y|GPIO_Pin_z|GPIO_Pin_t;

****************************************************************************/

void CH_Timer_GPIO_Configuration(GPIO_TypeDef* GPIOx, int GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOx, &GPIO_InitStructure);
}
/* -----------------------------------------------------------------------------------------------------
	 *
	 * TIMx Configuration: generate 1 PWM signals:
	 * APB1 prescaler = 72 # 1 => TIMxCLK = PCLK1x2 = 2 MHz, Prescaler = 0x0 => TIMx counter clock = 2 MHz
	 * TIMx ARR Register = 4096 => TIMx Frequency = TIMx counter clock/(ARR + 1)
	 * TIMx Frequency = 488.1620698Hz.
	 * TIMx Channel2 duty cycle = (TIMx_CCR2/ TIMx_ARR)* 100 = 50%	
	 * TIMx Frequency = TIMx counter clock/(TIM_Period + 1)
	 * Prescaler la gia tri de chia tu tan so he thong thanh gia tri can lay dua vao co timer
	 * Period la gia tri cua 100% xung PWM tao ra duoc va ti le phan tram xung (%) = (gia tri tu thanh ghi CCR)/Period
------------------------------------------------------------------------------------------------------ */

void PWM_timer_init(TIM_TypeDef* TIMx, int Period, int Prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = Period;
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;   // Gia tri nap vao thanh ghi CCR
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	TIM_OC2Init(TIMx, &TIM_OCInitStructure);
	TIM_OC3Init(TIMx, &TIM_OCInitStructure);
	TIM_OC4Init(TIMx, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);		
	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);		
	TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);		
	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);		

	TIM_ARRPreloadConfig(TIMx, ENABLE);

	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE);
}
void PWM_CH1(TIM_TypeDef* TIMx, uint16_t duty_cycle)
{
	TIMx->CCR1 = duty_cycle;	
}

void PWM_CH2(TIM_TypeDef* TIMx, uint16_t duty_cycle)
{
	TIMx->CCR2 = duty_cycle;	
}

void PWM_CH3(TIM_TypeDef* TIMx, uint16_t duty_cycle)
{
	TIMx->CCR3 = duty_cycle;	
}

void PWM_CH4(TIM_TypeDef* TIMx, uint16_t duty_cycle)
{
	TIMx->CCR4 = duty_cycle;	
}
void Timer3_init(void)
{
	
		NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* Khoi tao timer 2 thanh ngat 1 ms */

	 /* Enable the TIM2 gloabal Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel                      = TIM3_IRQn;	 // Khoi tao vecto ngat timer4
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 1;			 // Muc uu tien cua ngat
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;		 // Cho phep ngat

  	NVIC_Init(&NVIC_InitStructure);

  	/* TIM4 clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 // Enable Clock Timer2 on APB1 with frequency 36Mhz

/* ---------------------------------------------------------------------------//
    APB1 prescaler = 1 = 1 => PCLK2 = HCLK/1 => 72MHz/1 = 72MHz => 
 
    TIM1CLK = PCLK2 x 1 = 72 MHz, Prescaler = 71 => TIM2 counter clock = TIM2CLK /( Prescaler + 1 ) = 1 MHz
 
    TIM2 ARR Register = 65535 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
 
    / Time base configuration */
 
    TIM_TimeBaseStructure.TIM_Period = 65535;
 
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
 
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
		  	/* TIM IT enable */
  	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  	/* TIM2 enable counter */
  	//TIM_Cmd(TIM4, ENABLE);						  // Bat timer4
		TIM_Cmd(TIM3, DISABLE);
}
void TIM1_Configuration(void)
	{
		/* Cau hinh ngat*/
		NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	 /* Enable the TIM2 gloabal Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel                      = TIM1_UP_IRQn;	 // Khoi tao vecto ngat timer4
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 1;			 // Muc uu tien cua ngat
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;		 // Cho phep ngat
  	NVIC_Init(&NVIC_InitStructure);
		
    /* Enable clock to GPIOA, GPIOB and Timer1)*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

		/* Time base configuration */
		TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
		TIM_TimeBaseStructure.TIM_Period = 10000-1;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // tràn sau 10ms

		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
		
		 /* TIM IT enable */
  	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

		/* TIM1 enable counter */
//		TIM_Cmd(TIM1, ENABLE);
//		TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
void IO_config(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = (GPIO_Pin_0|GPIO_Pin_1);////////butt
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = (GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);//butt
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = (GPIO_Pin_1);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void RCC_Configuration(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
}
void USART1_Configuration(void)
{
	/* Configure PA9 for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PA10 for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);	
}

void _Delay_ms_mem(__IO uint32_t ms)
{
		long i;
		i = ms*10100;
		while(i)
		{
				i--;
		}
}
void _Delay_us_mem(__IO uint32_t us)
{
		long i;
		i = us*10;
		while(i)
		{
				i--;
		}
}
void Delay(__IO uint32_t num)
{
	__IO uint32_t index = 0;
	for(index = (720000 * num); index != 0; index--){}
}

void Delay_ms(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;
	while(TimingDelay != 0){}
}
//void Delay_ms(__IO uint32_t nTime)
//{ 
//	TimingDelay = nTime*1000;
//	while(TimingDelay != 0){}
//}
void TimingDelay_Decrement(void)
{	
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

void get_clock(void)
{
	RCC_ClocksTypeDef RCC_Config;
	RCC_GetClocksFreq(&RCC_Config);
	clk_freq = RCC_Config.PCLK2_Frequency;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/************************* linhkien69.vn ************************END OF FILE****/

