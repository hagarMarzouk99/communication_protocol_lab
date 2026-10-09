#include "UART.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)


void UART_Init(void)
{
    // Set baud rate
    UBRRH = (unsigned char)(UBRR_VALUE >> 8);
    UBRRL = (unsigned char)UBRR_VALUE;

    // Enable transmitter and receiver
    UCSRB = (1 << RXEN) |
            (1 << TXEN);

    // Frame format:
    // 8 data bits
    // 1 stop bit
    // No parity
    UCSRC = (1 << URSEL) |
            (1 << UCSZ1) |
            (1 << UCSZ0);
}


void UART_SendChar(unsigned char data)
{
    // Wait until transmit buffer is empty
    while (!(UCSRA & (1 << UDRE)));

    // Put data in UART Data Register
    UDR = data;
}


void UART_SendString(const char *str)
{
    while (*str != '\0')
    {
        UART_SendChar(*str);
        str++;
    }
}


unsigned char UART_ReceiveChar(void)
{
    // Wait until data is received
    while (!(UCSRA & (1 << RXC)));

    // Return received data
    return UDR;
}


void UART_SendTemperature_x2(int16_t temperature_x2)
{
    // Check if temperature is negative
    if (temperature_x2 < 0)
    {
        UART_SendChar('-');
        temperature_x2 = -temperature_x2;
    }

    // Calculate whole part
    int16_t whole = temperature_x2 / 2;

    // Calculate decimal part
    int16_t fraction = temperature_x2 % 2;


    // Print tens digit if needed
    if (whole >= 10)
    {
        UART_SendChar((whole / 10) + '0');
    }

    // Print units digit
    UART_SendChar((whole % 10) + '0');

    // Print decimal point
    UART_SendChar('.');

    // LM75 resolution is 0.5°C
    if (fraction == 0)
    {
        UART_SendChar('0');
    }
    else
    {
        UART_SendChar('5');
    }

    UART_SendString(" C");
}
void UART_SendTemperatureValue_x2(int16_t temperature_x2)
{
    // Send low byte first
    UART_SendChar((unsigned char)(temperature_x2 & 0xFF));

    // Send high byte
    UART_SendChar((unsigned char)((temperature_x2 >> 8) & 0xFF));
}