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

    // Send data
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


int16_t UART_ReceiveTemperature_x2(void)
{
    unsigned char low_byte;
    unsigned char high_byte;

    // Receive low byte first
    low_byte = UART_ReceiveChar();

    // Receive high byte
    high_byte = UART_ReceiveChar();

    // Combine the two bytes
    int16_t temperature_x2 =
        ((int16_t)high_byte << 8) | low_byte;

    return temperature_x2;
}