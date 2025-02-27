#ifndef __ENCODER_H
#define __ENCODER_H

void EncoderA_Init(void);
void EncoderB_Init(void);
void EncoderC_Init(void);
//void EncoderD_Init(void);
void SysTick_Init(void);
int16_t EncoderA_Get(void);
int16_t EncoderB_Get(void);
int16_t EncoderC_Get(void);
//int16_t EncoderD_Get(void);

#endif
