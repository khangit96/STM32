#include "stm32f4xx.h"
GPIO_InitTypeDef  GPIO_InitStructure;
void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);

int main(void)
{
  GPIO_Configuration();
  while (1)
  {
		/*
    if(GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0)==1)
    {
      GPIO_SetBits(GPIOD ,GPIO_Pin_14 | GPIO_Pin_15);
			
    }
    else
    {
      GPIO_ResetBits(GPIOD ,GPIO_Pin_14 | GPIO_Pin_15);
    }
		*/
		
		
		 GPIO_SetBits(GPIOD ,GPIO_Pin_5);
		 Delay(10000000);
     GPIO_ResetBits(GPIOD ,GPIO_Pin_5);
  	 Delay(10000000);
		
  }
}

void GPIO_Configuration(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA, ENABLE);

  /* Configure PD12 PD15 in output pushpull mode */
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;  //Bat den o chan 14, 15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //Bat den o chan 14, 15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* Configure PA0 in input mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;  //Thiet lap dien tro keo len doi voi nut bam
  GPIO_Init(GPIOA, &GPIO_InitStructure);
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

