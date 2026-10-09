#ifndef LM75_H
#define LM75_H

#include <stdint.h>

#define LM75_ADDRESS 0x48

void LM75_Init(void);

int16_t LM75_ReadTemperature_x2(void);

#endif