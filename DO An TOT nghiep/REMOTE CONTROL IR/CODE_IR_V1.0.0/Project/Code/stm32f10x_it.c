#include "stm32f10x_it.h"
#include "main.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/*******************************************************************************
* Function Name  	: WWDG_IRQHandler
* Description			: This function handles WWDG interrupt request.
* Notes						: 
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: PVD_IRQHandler
* Description			: This function handles PVD interrupt request.
* Notes			: 
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TAMPER_IRQHandler
* Description			: This function handles Tamper interrupt request. 
* Notes						: 
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: RTC_IRQHandler
* Description			: This function handles RTC global interrupt request.
* Notes						: 
*******************************************************************************/
void RTC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: FLASH_IRQHandler
* Description			: This function handles Flash interrupt request.
* Notes						: 
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: RCC_IRQHandler
* Description			: This function handles RCC interrupt request. 
* Notes						: 
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI0_IRQHandler
* Description			: This function handles External interrupt Line 0 request.
* Notes						: 
*******************************************************************************/

extern uint8_t Butt_Data_IR[32];
extern uint8_t Get_data,star_ok,ok_Data;
void EXTI0_IRQHandler(void)
{
	static uint8_t Bit_star=0,n;
	uint32_t T_IR;
	if(EXTI_GetITStatus(KEY_BUTTON_EXTI_LINE0) != RESET)		 // Kiem tra xem ngat xay ra hay chua
	{	
		T_IR = TIM_GetCounter(TIM2);
		TIM_SetCounter(TIM2,0);
//		printf("%d\r\n",T_IR);
		if(Bit_star==1)
		{
			if((T_IR>=2000)&&(T_IR<=2400))//Bit 1
			{
				Butt_Data_IR[n]=1;
				n++;
			}
			else if((T_IR>=1000)&&(T_IR<=1200))//bit 0
			{
				Butt_Data_IR[n]=0;
				n++;
			}
			else
			{
				n=0;
				Bit_star=0;
			}
			if(n==32)
			{
				n=0;
				Bit_star=0;
				Get_data=1;
			}
		}
		if((T_IR>=13000)&&(T_IR<=14000))
		{
			Bit_star=1;
		}
	}
	EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE0);
}

/*******************************************************************************
* Function Name  	: EXTI1_IRQHandler
* Description			: This function handles External interrupt Line 1 request.
* Notes						: 
*******************************************************************************/
void EXTI1_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  	: EXTI2_IRQHandler
* Description			: This function handles External interrupt Line 2 request.
* Notes						: 
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI3_IRQHandler
* Description			: This function handles External interrupt Line 3 request.
* Notes						: 
*******************************************************************************/
void EXTI3_IRQHandler(void)
{  

}

/*******************************************************************************
* Function Name  	: EXTI4_IRQHandler
* Description			: This function handles External interrupt Line 4 request.
* Notes						: 
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel1_IRQHandler
* Description			: This function handles DMA1 Channel 1 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel2_IRQHandler
* Description			: This function handles DMA1 Channel 2 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel3_IRQHandler
* Description			: This function handles DMA1 Channel 3 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel4_IRQHandler
* Description			: This function handles DMA1 Channel 4 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel5_IRQHandler
* Description			: This function handles DMA1 Channel 5 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel6_IRQHandler
* Description			: This function handles DMA1 Channel 6 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA1_Channel7_IRQHandler
* Description			: This function handles DMA1 Channel 7 interrupt request.
* Notes						: 
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: ADC1_2_IRQHandler
* Description			: This function handles ADC1 and ADC2 global interrupts requests.
* Notes						: 
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USB_HP_CAN_TX_IRQHandler
* Description			: This function handles USB High Priority or CAN TX interrupts requests.
* Notes						: 
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
  //CTR_HP();
}

/*******************************************************************************
* Function Name  	: USB_LP_CAN_RX0_IRQHandler
* Description			: This function handles USB Low Priority or CAN RX0 interrupts requests.
* Notes						: 
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
  //USB_Istr();
}

/*******************************************************************************
* Function Name  	: CAN_RX1_IRQHandler
* Description			: This function handles CAN RX1 interrupt request.
* Notes						: 
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: CAN_SCE_IRQHandler
* Description			: This function handles CAN SCE interrupt request.
* Notes						: 
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI9_5_IRQHandler
* Description			: This function handles External lines 9 to 5 interrupt request.
* Notes						: 
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{	
}

/*******************************************************************************
* Function Name  	: TIM1_BRK_IRQHandler
* Description			: This function handles TIM1 Break interrupt request.
* Notes						: 
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM1_UP_IRQHandler
* Description			: This function handles TIM1 overflow and update interrupt request.
* Notes						: 
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) // Update interrupt 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		BUTTON();
	}
}
/*******************************************************************************
* Function Name  	: TIM1_TRG_COM_IRQHandler
* Description			: This function handles TIM1 Trigger and commutation interrupts requests.
* Notes						: 
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM1_CC_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM1 capture compare interrupt request.
* Notes						: 
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM2_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM2 global interrupt request.
* Notes						: 
*******************************************************************************/
extern uint32_t n;
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // Update interrupt 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


/*******************************************************************************
* Function Name  	: TIM3_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM3 global interrupt request.
* Notes						: 
*******************************************************************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) // Update interrupt 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

/*******************************************************************************
* Function Name  	: TIM4_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM4 global interrupt request.
* Notes						: 
*******************************************************************************/
void TIM4_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  	: I2C1_EV_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles I2C1 Event interrupt request.
* Notes						: 
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: I2C1_ER_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles I2C1 Error interrupt request.
* Notes						: 
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: I2C2_EV_IRQHandler
* Return         	: None
* Parameters	 		: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles I2C2 Event interrupt request.
* Notes						: 
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: I2C2_ER_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles I2C2 Error interrupt request.
* Notes						: 
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SPI1_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles SPI1 global interrupt request.
* Notes						: 
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SPI2_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles SPI2 global interrupt request.
* Notes						: 
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USART1_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles USART1 global interrupt request.
* Notes			: 
*******************************************************************************/
void USART1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USART2_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles USART2 global interrupt request.
* Notes			: 
*******************************************************************************/
void USART2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USART3_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			:This function handles USART3 global interrupt request.
* Notes			: 
*******************************************************************************/
void USART3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: EXTI15_10_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles External lines 15 to 10 interrupt request.
* Notes			: 
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{		
}

/*******************************************************************************
* Function Name  	: RTCAlarm_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles RTC Alarm interrupt request.
* Notes			: 
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: USBWakeUp_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles USB WakeUp interrupt request.
* Notes			: 
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_BRK_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM8 Break interrupt request.
* Notes			: 
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_UP_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM8 overflow and update interrupt request.
* Notes			: 
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_TRG_COM_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM8 Trigger and commutation interrupts requests.
* Notes			: 
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM8_CC_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			:This function handles TIM8 capture compare interrupt request.
* Notes			: 
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: ADC3_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles ADC3 global interrupt request.
* Notes			: 
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: FSMC_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			:This function handles FSMC global interrupt request.
* Notes			: 
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SDIO_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles SDIO global interrupt request.
* Notes			: 
*******************************************************************************/
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
  //SD_ProcessIRQSrc();
}

/*******************************************************************************
* Function Name  	: TIM5_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM5 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: SPI3_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			:: This function handles SPI3 global interrupt request.
* Notes			: 
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: UART4_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			:This function handles UART4 global interrupt request.
* Notes			: 
*******************************************************************************/
void UART4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: UART5_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles UART5 global interrupt request.
* Notes			: 
*******************************************************************************/
void UART5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM6_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM6 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: TIM7_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles TIM7 global interrupt request.
* Notes			: 
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel1_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles DMA2 Channel 1 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel2_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles DMA2 Channel 2 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel3_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles DMA2 Channel 3 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  	: DMA2_Channel4_5_IRQHandler
* Return         	: None
* Parameters 			: None
* Created by			: linhkien69.vn
* Date created		: 28/02/2014
* Description			: This function handles DMA2 Channel 4 and DMA2 Channel 5 interrupt request.
* Notes			: 
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/************************* linhkien69.vn ************************END OF FILE****/
