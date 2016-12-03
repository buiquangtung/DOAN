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

#include "stm32_usart.h"

/*******************************************************************************
  --- Kiem tra file --- Kiem tra file --- Kiem tra file --- Kiem tra file ---
*******************************************************************************/
#if (__STM32_USART_H != 20150711)
    #error "Include Sai #File STM32_USART.H"
#endif




struct __FILE 
{
  int handle;                 // Add whatever you need here 
};
FILE __stdout;
FILE __stdin;

//extern uint8_t target; 

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

extern unsigned char RX_config,IP_counted,MYDNS_counted,Gateway_counted,SUBNET_counted;
extern unsigned char DATA_RECEIVED_CONFIG[50],SEND_DATA_CONFIG[50];
extern unsigned char status_ip,status_mydns,status_gateway,status_subnet;
PUTCHAR_PROTOTYPE
{
	if(target == 0)
	{
		usart1_send_data(ch);
		//USART_SendData(USART1, (uint8_t) ch);
		/* Loop until the end of transmission */
		//while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){} 
		 
		//return ch;
	}
	else if(target == 1)
	{
		usart2_send_data(ch);
		//USART_SendData(USART2, (uint8_t) ch);
		/* Loop until the end of transmission */
		//while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){} 
		 
		//return ch;
	}
	else
	{
		//lcd_Data_Write((ch));
	}
	return ch;
}

/*******************************************************************************
  fputc
*******************************************************************************/
//int fputc(int ch, FILE *f) 
//{
//	  if(target == 0)
//    {
//			return (usart1_send_data(ch));
//		}
//		else if( target == 1)
//		{
//			return (usart2_send_data(ch));
//		}
//		else
//		{
//			lcd_Data_Write((ch));
//		}
//}

/*******************************************************************************
//  fgetc
*******************************************************************************/
//int fgetc(FILE *f) 
//{
//	  if(target == 0)
//		{
//			return (usart1_send_data(usart1_get_data()));
//		}
//		else if( target == 1)
//		{
//			return (usart2_send_data(usart2_get_data()));
//		}
//}

void delay_ms_uart(unsigned long int t)
{
	unsigned long int i;
	for(i=0;i<t;i++)
	{}
}

/*******************************************************************************
	Ham nhan 1 ki tu !!! 
*******************************************************************************/
int usart1_send_data (int ch)  
{
	while (!(USART1->SR & USART_FLAG_TXE));
	USART1->DR = (ch & 0x1FF);

	return (ch);
}
/*******************************************************************************
	Ham nhan 1 ki tu !!! 
*******************************************************************************/
int usart1_get_data(void)  
{
	while (!(USART1->SR & USART_FLAG_RXNE));   // Kiem tra co nhan cho den khi nhan xong
	return ((int)(USART1->DR & 0x1FF));		     // Nhan du lieu tu cong USART1
}

int usart2_send_data (int ch)  
{
	while (!(USART2->SR & USART_FLAG_TXE));
	USART2->DR = (ch & 0x1FF);

	return (ch);
}
/*******************************************************************************
	Ham nhan 1 ki tu !!! 
*******************************************************************************/
int usart2_get_data(void)  
{
	while (!(USART2->SR & USART_FLAG_RXNE));   // Kiem tra co nhan cho den khi nhan xong
	return ((int)(USART2->DR & 0x1FF));		     // Nhan du lieu tu cong USART1
}

int usart3_send_data (int ch)  
{
	while (!(USART3->SR & USART_FLAG_TXE));
	USART3->DR = (ch & 0x1FF);

	return (ch);
}
/*******************************************************************************
	Ham nhan 1 ki tu !!! 
*******************************************************************************/
int usart3_get_data(void)  
{
	while (!(USART3->SR & USART_FLAG_RXNE));   // Kiem tra co nhan cho den khi nhan xong
	return ((int)(USART3->DR & 0x1FF));		     // Nhan du lieu tu cong USART1
}


/*******************************************************************************
Ham khoi tao USART voi cac cong USART1, USART2, USART3

USART1: TX PA9 -- RX PA10
USART2: TX PA2 -- RX PA3
USART3: TX PB10 -- RX PB11
********************************************************************************/
void usart1_init(GPIO_TypeDef* GPIO_x, int Pin_TX, int Pin_RX, long baudrate)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE); // Clock GPIOA, GPIOB


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* Configure PAx for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = Pin_TX;			         // Pin_TX cua USARTx (x=1,2,3)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   // Set up output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // Speed at GPIO_Pin
	GPIO_Init(GPIO_x, &GPIO_InitStructure);			       // define Portx
	

	/* Configure PAx for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = Pin_RX;				          // Pin_TX cua USARTx (x=1,2,3)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // Set up input
	GPIO_Init(GPIO_x, &GPIO_InitStructure);				        // define Portx
														  
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ClearFlag(USART1, USART_FLAG_RXNE);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
}

void usart2_init(GPIO_TypeDef* GPIO_x, int Pin_TX, int Pin_RX, long baudrate)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE); // Clock GPIOA, GPIOB


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* Configure PAx for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = Pin_TX;			   // Pin_TX cua USARTx (x=1,2,3)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   // Set up output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // Speed at GPIO_Pin
	GPIO_Init(GPIO_x, &GPIO_InitStructure);			   // define Portx
	

	/* Configure PAx for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = Pin_RX;				  // Pin_TX cua USARTx (x=1,2,3)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // Set up input
	GPIO_Init(GPIO_x, &GPIO_InitStructure);				  // define Portx
														  
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(USART2, &USART_InitStructure);
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_ClearFlag(USART2, USART_FLAG_RXNE);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* Enable USART */
	USART_Cmd(USART2, ENABLE);
}

void usart3_init(GPIO_TypeDef* GPIO_x, int Pin_TX, int Pin_RX, long baudrate)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE); // Clock GPIOA, GPIOB
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 

	/* Configure PAx for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = Pin_TX;			   // Pin_TX cua USARTx (x=1,2,3)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   // Set up output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // Speed at GPIO_Pin
	GPIO_Init(GPIO_x, &GPIO_InitStructure);			   // define Portx
	

	/* Configure PAx for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = Pin_RX;				  // Pin_TX cua USARTx (x=1,2,3)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // Set up input
	GPIO_Init(GPIO_x, &GPIO_InitStructure);				  // define Portx
														  
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(USART3, &USART_InitStructure);
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_ClearFlag(USART3, USART_FLAG_RXNE);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/* Enable USART */
	USART_Cmd(USART3, ENABLE);
}


void usart_send_data(USART_TypeDef* USARTx, char data)
{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){;}
		USART_SendData(USARTx, (uint16_t)data);
}

void usart1_send_string(const unsigned char* str)
{
		while(*str != '\0')
		{
				usart_send_data(USART1, *str++);
		}
}

void usart2_send_string(const char* str)
{
		while(*str != '\0')
		{
				usart_send_data(USART2, *str++);
		}
}

void usart3_send_string(const char* str)
{
		while(*str != '\0') 
		{
				usart_send_data(USART3, *str++);
		}
}
void In_Config_ethernet(void)
{
	unsigned char giatri;
	char i,jj=0,x=0,xx,counter=0,counter_tartus;
	unsigned char Number_A[3]="\0\0\0";
	unsigned char Number_B[3]="\0\0\0";
	unsigned char Number_C[3]="\0\0\0";
	unsigned char Number_D[3]="\0\0\0";
	for(x=0;x<50;x++)
	{
		DATA_RECEIVED_CONFIG[x]='\0';
	}
	for(x=0;x<3;x++)
	{
		Number_A[x]='\0';
		Number_B[x]='\0';
		Number_C[x]='\0';
		Number_D[x]='\0';
	}
	RX_config=0;
	counter=0;
	jj=0;
	while(status_ip==0){;}
	status_ip=0;
	usart1_send_string(DATA_RECEIVED_CONFIG);
	for(i=0;i<50;i++)
	{
		if(jj==0)
		{
			if(DATA_RECEIVED_CONFIG[i]== '=')
			{
				printf("\n gia tri i=%d",i);
				jj=1;
				x=0;
				counter=1;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx]!='.')
					{
						Number_A[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}	
					else xx=5;
				}
/*------------------------------------------------------------*/
				counter_tartus=counter;//4
				counter++;//5
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')//Config_ip=123.400.1.11$0A
					{
						Number_B[x]=DATA_RECEIVED_CONFIG[i+xx+counter_tartus];//
						x++;
						counter++;
					}
					else xx=5;
				}
/*-------------------------------------------------------*/
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=4;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+counter]!='.')
					{
						Number_C[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=5;
				}
/*-------------------------------------------------------*/
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=4;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+counter]!='.')
					{
						Number_D[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=5;
				}
			}
		}
	}
	target=0;
	giatri=converter_int(Number_A);
	EEP24CXX_WriteData(add_ip_A,giatri);
	printf("converter chuoi A = %d\n",giatri);
	giatri=converter_int(Number_B);
	EEP24CXX_WriteData(add_ip_B,giatri);
	printf("converter chuoi B = %d\n",giatri);
	giatri=converter_int(Number_C);
	EEP24CXX_WriteData(add_ip_C,giatri);
	printf("converter chuoi C = %d\n",giatri);
	giatri=converter_int(Number_D);
	EEP24CXX_WriteData(add_ip_D,giatri);
	printf("converter chuoi D = %d\n",giatri);
/*--------------------------------------------------------------------*/
	for(x=0;x<50;x++)
	{
		DATA_RECEIVED_CONFIG[x]='\0';
	}
	for(x=0;x<3;x++)
	{
		Number_A[x]='\0';
		Number_B[x]='\0';
		Number_C[x]='\0';
		Number_D[x]='\0';
	}
	RX_config=0;
	counter=0;
	jj=0;
	status_mydns=0;
	while(status_mydns==0){;}
	status_mydns=0;
	usart1_send_string(DATA_RECEIVED_CONFIG);
	for(i=0;i<50;i++)
	{
		if(jj==0)
		{
			if(DATA_RECEIVED_CONFIG[i]== '=')
			{
				jj=1;
				x=0;
				counter++;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx]!='.')
					{
						Number_A[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}	
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_B[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_C[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_D[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
			}
		}
	}
	target=0;
	giatri=converter_int(Number_A);
	EEP24CXX_WriteData(add_mydns_A,giatri);
	printf("converter chuoi A = %d\n",giatri);
	giatri=converter_int(Number_B);
	EEP24CXX_WriteData(add_mydns_B,giatri);
	printf("converter chuoi B = %d\n",giatri);
	giatri=converter_int(Number_C);
	EEP24CXX_WriteData(add_mydns_C,giatri);
	printf("converter chuoi C = %d\n",giatri);
	giatri=converter_int(Number_D);
	EEP24CXX_WriteData(add_mydns_D,giatri);
	printf("converter chuoi D = %d\n",giatri);
/*--------------------------------------------------------------------*/
	for(x=0;x<50;x++)
	{
		DATA_RECEIVED_CONFIG[x]='\0';
	}
	for(x=0;x<3;x++)
	{
		Number_A[x]='\0';
		Number_B[x]='\0';
		Number_C[x]='\0';
		Number_D[x]='\0';
	}
	RX_config=0;
	counter=0;
	jj=0;
	status_gateway=0;
	while(status_gateway==0){;}
	status_gateway=0;
	usart1_send_string(DATA_RECEIVED_CONFIG);
	for(i=0;i<50;i++)
	{
		if(jj==0)
		{
			if(DATA_RECEIVED_CONFIG[i]== '=')
			{
				jj=1;
				x=0;
				counter++;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx]!='.')
					{
						Number_A[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}	
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_B[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_C[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_D[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
			}
		}
	}
	target=0;
	giatri=converter_int(Number_A);
	EEP24CXX_WriteData(add_gateway_A,giatri);
	printf("converter chuoi A = %d\n",giatri);
	giatri=converter_int(Number_B);
	EEP24CXX_WriteData(add_gateway_B,giatri);
	printf("converter chuoi B = %d\n",giatri);
	giatri=converter_int(Number_C);
	EEP24CXX_WriteData(add_gateway_C,giatri);
	printf("converter chuoi C = %d\n",giatri);
	giatri=converter_int(Number_D);
	EEP24CXX_WriteData(add_gateway_D,giatri);
	printf("converter chuoi D = %d\n",giatri);
/*--------------------------------------------------------------------*/
	for(x=0;x<50;x++)
	{
		DATA_RECEIVED_CONFIG[x]='\0';
	}
	for(x=0;x<3;x++)
	{
		Number_A[x]='\0';
		Number_B[x]='\0';
		Number_C[x]='\0';
		Number_D[x]='\0';
	}
	RX_config=0;
	counter=0;
	jj=0;
	status_gateway=0;
	while(status_subnet==0){;}
	status_subnet=0;
	usart1_send_string(DATA_RECEIVED_CONFIG);
	for(i=0;i<50;i++)
	{
		if(jj==0)
		{
			if(DATA_RECEIVED_CONFIG[i]== '=')
			{
				jj=1;
				x=0;
				counter++;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx]!='.')
					{
						Number_A[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}	
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_B[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_C[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
				counter_tartus=counter;
				counter++;
				x=0;
				for(xx=1;xx<=3;xx++)
				{
					if(DATA_RECEIVED_CONFIG[i+xx+counter_tartus]!='.')
					{
						Number_D[x]=DATA_RECEIVED_CONFIG[i+counter];
						x++;
						counter++;
					}
					else xx=4;
				}
			}
		}
	}
	target=0;
	giatri=converter_int(Number_A);
	EEP24CXX_WriteData(add_subnet_A,giatri);
	printf("converter chuoi A = %d\n",giatri);
	giatri=converter_int(Number_B);
	EEP24CXX_WriteData(add_subnet_B,giatri);
	printf("converter chuoi B = %d\n",giatri);
	giatri=converter_int(Number_C);
	EEP24CXX_WriteData(add_subnet_C,giatri);
	printf("converter chuoi C = %d\n",giatri);
	giatri=converter_int(Number_D);
	EEP24CXX_WriteData(add_subnet_D,giatri);
	printf("converter chuoi D = %d\n",giatri);
}
unsigned char converter_int( unsigned char *data_conveter)
{
	uint8_t i,n=0;
	uint8_t sum;
	for(i=0;i<3;i++)
	{
		if((data_conveter[i]>=48)&&(data_conveter[i]<=57))
		{
			n++;
		}
		else i=4;
	}
	target=0;
	printf("do dai chuoi=%d\n",n);
	if(n==0)
	{
		sum=0;
	}
	else if( n==1)
	{
		sum = data_conveter[0]-48;
	}
	else if(n==2)
	{
		sum = ((data_conveter[0]-48)*10) + (data_conveter[1]-48);
	}
	else if(n==3)
	{
		sum = ((data_conveter[0]-48)*100) + ((data_conveter[1]-48)*10) + (data_conveter[2]-48);
	}
	return sum;
}

/*
int main()
{

	float i=0;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	usart_init(USART1, GPIOA, GPIO_Pin_9, GPIO_Pin_10, 115200);

	while(1)
	{
		printf("i: %f \n\r", i);
		i+=0.33333;
		delay(5);
	}
}
*/


/*******************************************************************************
  -----   LINHKIEN69   ---- LINHKIEN69   ---- LINHKIEN69  ---- LINHKIEN69 ---
*******************************************************************************/



