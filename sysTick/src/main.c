
#include <stm32f30x_conf.h>

RCC_ClocksTypeDef RCC_Clocks;
uint32_t sysTickFlag = 0;

void SysTick_Handler(void)
{
	sysTickFlag = 1;
}

void init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	//Provide clock to GPIO
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	//Initialize GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // Output
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int main(void)
{
  /* SysTick end of count event each 100ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 10);

  /* Initialize LEDs and User Button available on STM32F3-Discovery board */

  init();

  /* Infinite loop */
  while (1)
  {
		if(sysTickFlag == 1){
			sysTickFlag = 0;
			GPIO_Write(GPIOE, (GPIO_ReadOutputData(GPIOE)^0xFFFF));
		}
	}
}
