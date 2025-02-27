#ifndef __ENCODER_H
#define __ENCODER_H

void Encoder_Init(void);
void SysTick_Init(void);
int16_t EncoderA_Get(void);
int16_t EncoderB_Get(void);
int16_t EncoderC_Get(void);
int16_t EncoderD_Get(void);

#endif
