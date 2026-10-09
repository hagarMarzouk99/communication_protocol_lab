#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>

void UART_Init(void);

void UART_SendChar(unsigned char data);

void UART_SendString(const char *str);

unsigned char UART_ReceiveChar(void);

void UART_SendTemperature_x2(int16_t temperature_x2);
void UART_SendTemperatureValue_x2(int16_t temperature_x2);

#endif