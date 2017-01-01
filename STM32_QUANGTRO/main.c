#include "stm32f4xx.h"
GPIO_InitTypeDef  GPIO_InitStructure;
void GPIO_initPD3(void);
void GPIO_initPD5(void);
void Delay(__IO uint32_t nCount);

int main(void)
{
	GPIO_initPD3();
	GPIO_initPD5();
  while (1)
  {
		int value=GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5);
	   if(value>-9)
			 {
				 
				 		 GPIO_SetBits(GPIOD ,GPIO_Pin_3);
			}
			 else
				{
					 GPIO_ResetBits(GPIOD ,GPIO_Pin_3);
				}
		
		
		
  }
}

void GPIO_initPD5()
	{
		//Config PD5
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	 GPIO_InitTypeDef pin;
   pin.GPIO_Pin = GPIO_Pin_5;
   pin.GPIO_Mode = GPIO_Mode_IN;
   pin.GPIO_Speed = GPIO_Speed_2MHz;
   pin.GPIO_OType = GPIO_OType_PP;
   pin.GPIO_PuPd = GPIO_PuPd_UP; 
   GPIO_Init(GPIOD, &pin);
	}
void GPIO_initPD3()
	{
		/* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* Configure the PD5 pin in output pushpull mode */
  GPIO_InitTypeDef led;
  led.GPIO_Pin = GPIO_Pin_3;
  led.GPIO_Mode = GPIO_Mode_OUT;
  led.GPIO_OType = GPIO_OType_PP;
  led.GPIO_Speed = GPIO_Speed_2MHz;
  led.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOD, &led);
	}
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT
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

