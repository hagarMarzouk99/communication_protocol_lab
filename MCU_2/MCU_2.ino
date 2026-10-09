#include "UART.h"
#include "LCD.h"


void setup()
{
    // Initialize UART
    UART_Init();

    // Initialize LCD
    LCD_Init();

    // Display startup message
    LCD_Clear();

    LCD_SetCursor(0, 0);
    LCD_SendString("Temperature:");
}


void loop()
{
    int16_t temperature_x2;


    // Receive temperature from MCU1
    temperature_x2 = UART_ReceiveTemperature_x2();


    // Display temperature
    LCD_SetCursor(0, 1);

    LCD_SendTemperature_x2(temperature_x2);
}