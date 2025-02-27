#include "stm32f10x.h"                  // Device header
#include "PWM.h"


void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//将PA4和PA5引脚初始化为推挽输出	

         RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	GPIO_InitTypeDef GI;
	GI.GPIO_Mode = GPIO_Mode_Out_PP;
	GI.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12;
	GI.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GI);      

	PWM_Init();
	PWM2_Init();
	PWM3_Init();
	PWM4_Init();//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：Speed 要设置的速度，范围：-100~100
  * 返 回 值：无
  */

void MotorA_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);	//PA4置高电平
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);	//PA5置低电平，设置方向为正转
		PWM_SetCompare3(Speed);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);	//PA4置低电平
		GPIO_SetBits(GPIOA, GPIO_Pin_5);	//PA5置高电平，设置方向为反转
		PWM_SetCompare3(-Speed);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}
void MotorD_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);	//PA11置高电平
		GPIO_ResetBits(GPIOA, GPIO_Pin_12);	//PA12置低电平，设置方向为正转
		PWM2_SetCompare3(Speed);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);	//PA11置低电平
		GPIO_SetBits(GPIOA, GPIO_Pin_12);	//PA12置高电平，设置方向为反转
		PWM2_SetCompare3(-Speed);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}
void MotorC_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_13);	//PA11置高电平
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//PA12置低电平，设置方向为正转
		PWM3_SetCompare3(Speed);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);	//PA11置低电平
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	//PA12置高电平，设置方向为反转
		PWM3_SetCompare3(-Speed);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}
void MotorB_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);	//PA11置高电平
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	//PA12置低电平，设置方向为正转
		PWM4_SetCompare3(Speed);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);	//PA11置低电平
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	//PA12置高电平，设置方向为反转
		PWM4_SetCompare3(-Speed);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}