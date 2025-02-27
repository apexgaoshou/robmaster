#include "stm32f10x.h"

void LED_INIT(void)
{	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gi;
	gi.GPIO_Mode=GPIO_Mode_Out_PP;
	gi.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	gi.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gi);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);




}

void LED1_ON(){

	GPIO_ResetBits(GPIOA,GPIO_Pin_1);


}
void LED1_OFF(){

	GPIO_SetBits(GPIOA,GPIO_Pin_1);


}
void LED2_ON(){

	GPIO_ResetBits(GPIOA,GPIO_Pin_2);


}
void LED2_OFF(){

	GPIO_SetBits(GPIOA,GPIO_Pin_2);


}
void LED1_TURN(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);

	}
}
void LED2_TURN(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{	
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);

	}
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
