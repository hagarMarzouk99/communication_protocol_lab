#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>

void UART_Init(void);

void UART_SendChar(unsigned char data);

void UART_SendString(const char *str);

unsigned char UART_ReceiveChar(void);

int16_t UART_ReceiveTemperature_x2(void);

#endif