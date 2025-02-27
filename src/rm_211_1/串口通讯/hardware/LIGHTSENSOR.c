#include "stm32f10x.h"


void LIGHTSENSOR_INIT(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gi;
	gi.GPIO_Mode=GPIO_Mode_IPU;
	gi.GPIO_Pin=GPIO_Pin_13;
	gi.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gi);
}
uint8_t LIGHTSENSOR_GET()
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}

