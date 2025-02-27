 #include "stm32f10x.h"                  // Device header

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
void PWM_Init(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//开启TIM2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							//将PA2引脚初始化为复用推挽输出	
																	//受外设控制的引脚，均需要配置为复用模式
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM2);		//选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 //计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;               //预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元
	
	/*输出比较初始化*/ 
	TIM_OCInitTypeDef TIM_OCInitStructure;							//定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);                         //结构体初始化，若结构体没有完整赋值
	                                                                //则最好执行此函数，给结构体所有成员都赋一个默认值
	                                                                //避免结构体初值不确定的问题
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //输出比较模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;								//初始的CCR值
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);                        //将结构体变量交给TIM_OC3Init，配置TIM2的输出比较通道3
	
	/*TIM使能*/
	TIM_Cmd(TIM2, ENABLE);			//使能TIM2，定时器开始运行
}
void PWM2_Init(void)
{
    /* 开启时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 开启TIM3的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 开启GPIOB的时钟

    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      // 复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;            // 配置PB0引脚（TIM3的CH3通道）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 设置GPIO速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // 初始化PB0引脚为复用推挽输出

    /* 配置时钟源 */
    TIM_InternalClockConfig(TIM3);  // 选择TIM3为内部时钟，TIM默认也是内部时钟，不调用此函数也可

    /* 时基单元初始化 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;  // 设置计数周期（ARR值）
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;  // 设置预分频（PSC值）
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;  // 设置重复计数器
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);  // 初始化TIM3时基单元

    /* 输出比较初始化 */
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);  // 结构体初始化，赋初值
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  // 设置PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // 输出极性高
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  // 使能输出
    TIM_OCInitStructure.TIM_Pulse = 0;  // 设置初始的CCR值
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  // 配置TIM3的CH3输出通道

    /* TIM使能 */
    TIM_Cmd(TIM3, ENABLE);  // 启动TIM3
}
void PWM3_Init(void)
{
    /* 开启时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 开启TIM3的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 开启GPIOB的时钟

    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      // 复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            // 配置PB0引脚（TIM3的CH3通道）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 设置GPIO速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // 初始化PB0引脚为复用推挽输出

    /* 配置时钟源 */
    TIM_InternalClockConfig(TIM3);  // 选择TIM3为内部时钟，TIM默认也是内部时钟，不调用此函数也可

    /* 时基单元初始化 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;  // 设置计数周期（ARR值）
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;  // 设置预分频（PSC值）
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;  // 设置重复计数器
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);  // 初始化TIM3时基单元

    /* 输出比较初始化 */
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);  // 结构体初始化，赋初值
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  // 设置PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // 输出极性高
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  // 使能输出
    TIM_OCInitStructure.TIM_Pulse = 0;  // 设置初始的CCR值
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);  // 配置TIM3的CH3输出通道

    /* TIM使能 */
    TIM_Cmd(TIM3, ENABLE);  // 启动TIM3
}
void PWM4_Init(void)
{
    /*开启时钟*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);             //开启TIM2的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);             //开启GPIOA的时钟
    
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   //复用推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                        //PA3引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 //50MHz的IO口速度
    GPIO_Init(GPIOA, &GPIO_InitStructure);                             //初始化GPIOA的PA11引脚为复用推挽输出模式
    
    /*配置时钟源*/
    TIM_InternalClockConfig(TIM2);                                     //选择TIM2为内部时钟源
    
    /*时基单元初始化*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                  //定义时基结构体变量
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //时钟分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //计数模式，向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                     //ARR的值，计数周期
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;                   //PSC的值，预分频
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                //高级定时器使用
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);                 //配置TIM2的时基单元
    
    /*输出比较初始化*/
    TIM_OCInitTypeDef TIM_OCInitStructure;                              //定义输出比较结构体
    TIM_OCStructInit(&TIM_OCInitStructure);                             //初始化结构体
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                   //选择PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //输出极性为高
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //使能输出
    TIM_OCInitStructure.TIM_Pulse = 0;                                  //设置初始CCR值为0
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);                            //配置TIM2的CH4通道
    
    /*TIM使能*/
    TIM_Cmd(TIM2, ENABLE);                                              //使能TIM2定时器
}

/**
  * 函    数：PWM设置CCR
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);		
}
void PWM2_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare4(TIM3, Compare);		
}
void PWM3_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM3, Compare);
}
void PWM4_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare4(TIM2, Compare);
}