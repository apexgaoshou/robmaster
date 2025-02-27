#ifndef __SERIAL_H
#define __SERIAL_H
#include "stdio.h"
void SERIALSENDDATA(uint8_t Byte);
void SERIALINIT(void);
void SENDARRAY(uint8_t *array,uint16_t length);

#endif