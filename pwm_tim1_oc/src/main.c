// This is an example to use timer 1 output compare for PWM
//
// When you execute this,
// LED3 will lit with less brightness.

#include "stm32f30x_conf.h"

#define F_CYCLE (72*1000*1000) // Cycles per second

/*typedefs*/
void init(void);
void init_timer(void);


void init(){
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_2); // Set AF for TIM1

  init_timer();
}

void init_timer(){

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // provide clock to tim1

  TIM_TimeBaseStructure.TIM_Period = F_CYCLE/0x8000-1; // Set to about 0.2 us. Timer counts up to TIM_Period + 1
  TIM_TimeBaseStructure.TIM_Prescaler = 0; // Prescaler ratio will be TIM_Prescaler + 1
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; // No dead time
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = F_CYCLE/8/0x8000-1; // set PWM duty to 1/8
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_Cmd(TIM1, ENABLE);

  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

int main(){
  init();

  while(1);
}
