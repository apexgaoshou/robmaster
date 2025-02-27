#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "bluetooth.h"
#include "Key.h"
#include "Motor.h"
#include "encoder.h"
#include "connect.h"
/*
motorA
PA2 TIM2-CH3
PA4 
PA5
PA6 TIM3-CH1
PA7 TIM3-CH2
motorB
PA3 TIM2-CH4
PA0
PA1
PA8 TIM1-CH1
PA9 TIM1-CH2
motorC
PB0 TIM3-CH3
PB12
PB13
PB6 TIM4-CH1
PB7 TIM4-CH2
motorD 
PB1 TIM3-CH4
PA11
PA12
PB8 TIM4_CH3
PB9 TIM4_CH4
*/
uint8_t KeyNum;		//�������ڽ��հ�������ı���
int16_t SpeedA;
int16_t SpeedB;
int16_t SpeedC;
int16_t SpeedD;
extern uint8_t Connect_TxPacket[4];				//���巢�����ݰ����飬���ݰ���ʽ��FF 01 02 03 04 FE
extern uint8_t Connect_RxPacket[4];				//����������ݰ�����
extern uint8_t Connect_RxFlag;
int main(void)
{
	
	OLED_Init();		//OLED��ʼ��
	//Serial_Init();		//���ڳ�ʼ��
	Connect_Init();
	Encoder_Init();
	//Motor_Init();	
	SysTick_Init();
	
	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");
	while(1)
	{
	
//	MotorA_SetSpeed(20);
//		
//	MotorB_SetSpeed(20);
//		
//	MotorC_SetSpeed(20);
//		
//	MotorD_SetSpeed(20);
	if (Connect_GetRxFlag() == 1)	//������յ����ݰ�
		{
			OLED_ShowHexNum(4, 1, Connect_RxPacket[0], 2);	//��ʾ���յ����ݰ�
			OLED_ShowHexNum(4, 4, Connect_RxPacket[1], 2);
			OLED_ShowHexNum(4, 7, Connect_RxPacket[2], 2);
			OLED_ShowHexNum(4, 10, Connect_RxPacket[3], 2);
		}
	Connect_TxPacket[0]=1;
	Connect_TxPacket[1]=2;
	Connect_TxPacket[2]=3;
	Connect_TxPacket[3]=4;
		
	Connect_SendPacket();
	}
}
