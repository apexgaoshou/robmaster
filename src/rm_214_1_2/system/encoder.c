#include "stm32f10x.h"  // Device header

volatile uint32_t sysTickCount = 0;        // SysTick �жϼ���
volatile int32_t encoderDelta = 0;         // �����������ֵ
volatile int32_t encoderLastValue = 0;     // ��һ�α���������ֵ
extern int16_t SpeedA;
extern int16_t SpeedB;
extern int16_t SpeedC;
extern int16_t SpeedD;
	
void Encoder_Init(void)
{
    /* ����ʱ�� */
    // TIM2ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // PA2, PA3

    // TIM3ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // PA6, PA7

    // TIM1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // PA8, PA9

    // TIM4ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // PB6, PB7

    /* GPIO��ʼ�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    // PA2��PA3 (TIM2)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PA6��PA7 (TIM3)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PA8��PA9 (TIM1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PB6��PB7 (TIM4)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* ʱ����Ԫ��ʼ�� */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // TIM2ʱ����ʼ��
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    // TIM3ʱ����ʼ��
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    // TIM1ʱ����ʼ��
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    // TIM4ʱ����ʼ��
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    /* ���벶���ʼ�� */
    TIM_ICInitTypeDef TIM_ICInitStructure;

    // TIM2 ���벶���ʼ��
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    // TIM3 ���벶���ʼ��
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // TIM1 ���벶���ʼ��
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    // TIM4 ���벶���ʼ��
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    /* �������ӿ����� */
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    /* ������ʱ�� */
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}


int16_t EncoderA_Get(void)
{
	/*ʹ��Temp������Ϊ�м̣�Ŀ���Ƿ���CNT��������*/
	int16_t Temp;
	Temp = TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2, 0);
	return Temp;
}

int16_t EncoderB_Get(void)
{
	/*ʹ��Temp������Ϊ�м̣�Ŀ���Ƿ���CNT��������*/	
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return Temp;
}

int16_t EncoderC_Get(void)
{
	/*ʹ��Temp������Ϊ�м̣�Ŀ���Ƿ���CNT��������*/
	int16_t Temp;
	Temp = TIM_GetCounter(TIM1);
	TIM_SetCounter(TIM1, 0);
	return Temp;
}

int16_t EncoderD_Get(void)
{
	/*ʹ��Temp������Ϊ�м̣�Ŀ���Ƿ���CNT��������*/
	int16_t Temp;
	Temp = TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4, 0);
	return Temp;
}

// ��ʼ�� SysTick��1ms �жϣ�
void SysTick_Init(void) {
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;  // 1ms �ж�
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk | 
                   SysTick_CTRL_ENABLE_Msk;
}

// SysTick �жϷ�����
void SysTick_Handler(void) {
    sysTickCount++;
    
    // ÿ 100ms ִ��һ�β���
    if (sysTickCount % 100 == 0) {
         
	SpeedA = EncoderA_Get();
	SpeedB = EncoderB_Get();
	SpeedC = EncoderC_Get();
	SpeedD = EncoderD_Get();
    }
}
