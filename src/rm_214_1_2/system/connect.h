#ifndef __CONNECT_H
#define __CONNECT_H

#include <stdio.h>

extern uint8_t Connect_TxPacket[];
extern uint8_t Connect_RxPacket[];

void Connect_Init(void);
void Connect_SendByte(uint8_t Byte);
void Connect_SendArray(uint8_t *Array, uint16_t Length);
void Connect_SendString(char *String);
void Connect_SendNumber(uint32_t Number, uint8_t Length);
void Connect_Printf(char *format, ...);

void Connect_SendPacket(void);
uint8_t Connect_GetRxFlag(void);

#endif