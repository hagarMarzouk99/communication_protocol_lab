#include "I2C.h"
#include "LM75.h"
#include "UART.h"


void setup()
{
    I2C_Init();

    LM75_Init();

    UART_Init();

}


void loop()
{
    int16_t temperature_x2;

    // Read temperature from LM75
    temperature_x2 = LM75_ReadTemperature_x2();

    // Send temperature value to MCU2
    UART_SendTemperatureValue_x2(temperature_x2);

    // Delay
    for (volatile long i = 0; i < 500000; i++);
}