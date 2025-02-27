#include "stm32f10x.h"
#include "stdio.h"

      
void SERIALINIT(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GI;
	GI.GPIO_Mode=GPIO_Mode_AF_PP;	
	GI.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GI.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&GI);

	USART_InitTypeDef UI;
	
	UI.USART_BaudRate=9600;
	UI.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	UI.USART_Mode=USART_Mode_Tx;
	UI.USART_Parity=USART_Parity_No;
	UI.USART_StopBits=USART_StopBits_1;
	UI.USART_WordLength=USART_WordLength_8b;
		
	USART_Init(USART1,&UI);
	
	USART_Cmd(USART1,ENABLE);

	
}

void SERIALSENDDATA(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
	


}

void SENDARRAY(uint8_t *array,uint16_t length)
{
	uint16_t i;
	for(i=0;i<length;i++)
	{
		SERIALSENDDATA(array[i]);	
	}
	




}
//printfÖØ¶¨Ïò


int fputc(int ch,FILE *f)
{
	SERIALSENDDATA(ch);
	return ch;
	
	
	
}




