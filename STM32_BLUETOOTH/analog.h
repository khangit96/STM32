#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_ADC.h"


//**************
	uint8_t ADCResult;


void RCC_Configuration_Adc1(void)
{
  //for ADC1 on PC0 using IN10
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

void GPIO_Configuration_Adc1(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure);

  //for ADC1 on PC0 using IN10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void ADC1_Configuration(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef       ADC_InitStructure;

  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

  ADC_CommonInit(&ADC_CommonInitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;


  ADC_StructInit(&ADC_InitStructure);

  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles);
  ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);

  ADC_Cmd(ADC1, ENABLE);    //The ADC is powered on by setting the ADON bit in the ADC_CR2 register.
  //When the ADON bit is set for the first time, it wakes up the ADC from the Power-down mode.
}



//************


void ftoa(float f, unsigned char *buf, char DecPoint)

{
   unsigned int rem;
   unsigned char *s,length=0;
   unsigned char a;
   int i;



   i = (int)((float)f*1000); //1000 : 4 chiffre //nombre de chiffre a prendre en compte
   s = buf;
  if (i == 0)                //print 0.0 with null termination here
   {
      *s++ = '0';
      *s++ = '.';
      *s++ = '0';
      *s=0;                   //null terminate the string
   }
   else
   {
      if (i < 0)
      {
         *buf++ = '-';
         s = buf;
         i = -i;
      }
      //while-loop to "decode" the long integer to ASCII by append '0', string in reverse manner
      //If it is an integer of 124 -> string = {'4', '2', '1'}
      while (i)
      {
         ++length;
         rem = i % 10;
         *s++ = rem + '0';
         i /= 10;
      }
      //reverse the string in this for-loop, string became {'1', '2', '4'} after this for-loop
  /*    for(rem=0; ((unsigned char)rem)<length/2; rem++)
      {
         *(buf+length) = *(buf+((unsigned char)rem));
         *(buf+((unsigned char)rem)) = *(buf+(length-((unsigned char)rem)-1));
         *(buf+(length-((unsigned char)rem)-1)) = *(buf+length);
      }*/
      for(rem=0; ((unsigned char)rem)<length/2; rem++)
      {
    	  a=buf[rem];
    	  buf[rem]=buf[length-rem-1];
    	  buf[length-rem-1]= a;
      }
      //translation
      for(rem=1; ((unsigned char)rem)<=length; rem++)
      {
    	  buf[length-rem+1]=buf[length-rem];
      }

      /* Take care of the special case of 0.x if length ==1*/
     if(length==1)
      {
         *(buf+2) = *buf;
         *buf = '0';
         *(buf+1) = '.';

         *(s+2)=0;                //null terminate
      }
      else
      {
           *(buf+length) = *(buf+length-0);
            *(buf+length-3)='.';          //3 : trois chiffres aprés la virgule//
            *(s+2)=0;                   //null terminate
      }
   }
  /* buf[length+1]='V';
   for(i=length+2; i<=16; i++)
           	      {
           	    	  buf[i]=' ';
           	      }*/

}
