#include "stm32f4xx.h"
GPIO_InitTypeDef  led,pin;

void GPIO_InitLed(void);
void GPIO_initPD5(void);
void GPIO_initPD3(void);
void blinkLed(void);
void resetLed(void);

void Delay(__IO uint32_t nCount);

int main(void)
{
  GPIO_InitLed();
	GPIO_initPD5();
	GPIO_initPD3();
	
  while (1)
  {
	
		 if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5)) 
		 {
			 blinkLed();
			  
     } 
		 else
		 {
			 resetLed();
      }
	   
		
	
		
  }
}

void blinkLed()
	{
		 GPIO_SetBits(GPIOD ,GPIO_Pin_3);
		// Delay(10000000);
	  // GPIO_ResetBits(GPIOD ,GPIO_Pin_3);
    // Delay(10000000);
	}
	
	void resetLed()
		{
		 GPIO_ResetBits(GPIOD ,GPIO_Pin_3);

		}
void GPIO_InitLed()
{
	//Config Led
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA, ENABLE);

  /* Configure PD12 PD15 in output pushpull mode */
	led.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;  //Bat den o chan 14, 15
  led.GPIO_Mode = GPIO_Mode_OUT;
  led.GPIO_OType = GPIO_OType_PP;
  led.GPIO_Speed = GPIO_Speed_100MHz;
  led.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &led);
	
  /* Configure PA0 in input mode */
  led.GPIO_Pin = GPIO_Pin_0;
  led.GPIO_Mode = GPIO_Mode_IN;
  led.GPIO_PuPd = GPIO_PuPd_DOWN;  //Thiet lap dien tro keo len doi voi nut bam
  GPIO_Init(GPIOA, &led);
	
}
void GPIO_initPD5()
	{
		//Config PD5
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
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

