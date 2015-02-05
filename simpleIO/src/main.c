// This is an example to use GPIO
//
// When you push user switch on the board,
// all LEDs lit.

#include "stm32f30x_conf.h"
void init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	//Provide clock to GPIOA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	//Initialize GPIOA P0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //This is the user switch on board
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Input
	GPIO_InitStructure.GPIO_OType = GPIO_PuPd_NOPULL; // No push up or pull down
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Provide clock to GPIOE
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	//Initialize GPIOE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; // These are connected to LEDs
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // Output
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int main(void)
{
  int switch_state = 0;

  init();
  while(1)
  {
    switch_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); // Read switch state
    GPIO_Write(GPIOE, switch_state * 0xFFFF); // Output to all LEDs
  }
}
