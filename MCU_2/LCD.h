#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <stdint.h>

void LCD_Init(void);

void LCD_Command(unsigned char command);

void LCD_SendChar(unsigned char data);

void LCD_SendString(const char *str);

void LCD_Clear(void);

void LCD_SetCursor(unsigned char row, unsigned char column);

void LCD_SendTemperature_x2(int16_t temperature_x2);

#endif