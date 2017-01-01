
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
int i;

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef     GPIO_InitStruct;
 
// Enable clock for GPIOA
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 
/**
* Tell pins PA9 and PA10 which alternating function you will use
* @important Make sure, these lines are before pins configuration!
*/
 GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
// Initialize pins as alternating function
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void USART_Configuration(void)
{
USART_InitTypeDef USART_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
 
/**
 * Enable clock for USART1 peripheral
 */
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
 
/**
 * Set Baudrate to value you pass to function
 * Disable Hardware Flow control
 * Set Mode To TX and RX, so USART will work in full-duplex mode
 * Disable parity bit
 * Set 1 stop bit
 * Set Data bits to 8
 *
 * Initialize USART1
 * Activate USART1
 */
USART_InitStruct.USART_BaudRate =9600;
USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
USART_InitStruct.USART_Parity = USART_Parity_No;
USART_InitStruct.USART_StopBits = USART_StopBits_1;
USART_InitStruct.USART_WordLength = USART_WordLength_8b;
USART_Init(USART1, &USART_InitStruct);
USART_Cmd(USART1, ENABLE);
 
/**
 * Enable RX interrupt
 */
USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
 
/**
 * Set Channel to USART1
 * Set Channel Cmd to enable. That will enable USART1 channel in NVIC
 * Set Both priorities to 0. This means high priority
 *
 * Initialize NVIC
 */
NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
NVIC_Init(&NVIC_InitStruct);

  /* Enable USART1 */
  USART_Cmd(USART1, ENABLE);
}
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount)
{
    //
    // Loop while there are more characters to send.
    //
    while(ulCount--)
    {
        USART_SendData(USART1, (uint16_t) *pucBuffer++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        {
        }
    }
}
void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
	{
		i = USART_ReceiveData(USART1);
		if(i == '1'){
			GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);		// Set '1' on PA8
			UARTSend("LED ON\r\n",sizeof("LED ON\r\n"));	// Send message to UART1
		}
		else if(i == '0'){
			GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// Set '0' on PA8
			UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
		}
	}
}
void usart_rxtx(void)
{
    const unsigned char welcome_str[] = " Welcome to Bluetooth!\r\n";

    /* Enable USART1 and GPIOA clock */
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* NVIC Configuration */
   // NVIC_Configuration();

    /* Configure the GPIOs */
    GPIO_Configuration();

    /* Configure the USART1 */
    USART_Configuration();

    /* Enable the USART1 Receive interrupt: this interrupt is generated when the
         USART1 receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* print welcome information */
    UARTSend(welcome_str, sizeof(welcome_str));
}
int main()
	{
		usart_rxtx();
    while(1)
    {

    }
	}