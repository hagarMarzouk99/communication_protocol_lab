#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

void I2C_Init(void);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_Write(unsigned char data);

unsigned char I2C_Read_ACK(void);

unsigned char I2C_Read_NACK(void);

#endif