#include "LCD.h"


// ===============================
// LCD DATA PORT
// ===============================

#define LCD_DATA_PORT PORTA
#define LCD_DATA_DDR  DDRA


// ===============================
// LCD CONTROL PORT
// ===============================

#define LCD_CONTROL_PORT PORTB
#define LCD_CONTROL_DDR  DDRB

#define LCD_RS PB0
#define LCD_RW PB1
#define LCD_EN PB2


// ===============================
// Delay Function
// ===============================

void LCD_Delay(void)
{
    for (volatile long i = 0; i < 2000; i++);
}


// ===============================
// Send Command
// ===============================

void LCD_Command(unsigned char command)
{
    // RS = 0 → Command
    LCD_CONTROL_PORT &= ~(1 << LCD_RS);

    // RW = 0 → Write
    LCD_CONTROL_PORT &= ~(1 << LCD_RW);

    // Put command on data bus
    LCD_DATA_PORT = command;

    // Enable pulse
    LCD_CONTROL_PORT |= (1 << LCD_EN);

    LCD_Delay();

    LCD_CONTROL_PORT &= ~(1 << LCD_EN);

    LCD_Delay();
}


// ===============================
// Send Character
// ===============================

void LCD_SendChar(unsigned char data)
{
    // RS = 1 → Data
    LCD_CONTROL_PORT |= (1 << LCD_RS);

    // RW = 0 → Write
    LCD_CONTROL_PORT &= ~(1 << LCD_RW);

    // Put data on data bus
    LCD_DATA_PORT = data;

    // Enable pulse
    LCD_CONTROL_PORT |= (1 << LCD_EN);

    LCD_Delay();

    LCD_CONTROL_PORT &= ~(1 << LCD_EN);

    LCD_Delay();
}


// ===============================
// Send String
// ===============================

void LCD_SendString(const char *str)
{
    while (*str != '\0')
    {
        LCD_SendChar(*str);
        str++;
    }
}


// ===============================
// Clear LCD
// ===============================

void LCD_Clear(void)
{
    LCD_Command(0x01);

    LCD_Delay();
}


// ===============================
// Set Cursor
// ===============================

void LCD_SetCursor(unsigned char row, unsigned char column)
{
    unsigned char address;


    if (row == 0)
    {
        address = 0x80 + column;
    }
    else
    {
        address = 0xC0 + column;
    }


    LCD_Command(address);
}


// ===============================
// LCD Initialization
// ===============================

void LCD_Init(void)
{
    // Set PORTA as output
    LCD_DATA_DDR = 0xFF;


    // Set PB0, PB1, PB2 as output
    LCD_CONTROL_DDR |=
        (1 << LCD_RS) |
        (1 << LCD_RW) |
        (1 << LCD_EN);


    // Initial states
    LCD_CONTROL_PORT &= ~(1 << LCD_RS);
    LCD_CONTROL_PORT &= ~(1 << LCD_RW);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN);


    // Wait for LCD power-up
    for (volatile long i = 0; i < 10000; i++);


    // 8-bit mode
    LCD_Command(0x38);


    // Display ON, Cursor OFF
    LCD_Command(0x0C);


    // Clear display
    LCD_Command(0x01);


    // Entry mode
    LCD_Command(0x06);


    LCD_Delay();
}


// ===============================
// Display Temperature
// ===============================

void LCD_SendTemperature_x2(int16_t temperature_x2)
{
    int16_t whole;
    int16_t fraction;


    // Handle negative temperature
    if (temperature_x2 < 0)
    {
        LCD_SendChar('-');

        temperature_x2 = -temperature_x2;
    }


    // Whole part
    whole = temperature_x2 / 2;


    // Fraction
    fraction = temperature_x2 % 2;


    // Tens digit
    if (whole >= 10)
    {
        LCD_SendChar((whole / 10) + '0');
    }


    // Units digit
    LCD_SendChar((whole % 10) + '0');


    // Decimal point
    LCD_SendChar('.');


    // 0.0 or 0.5
    if (fraction == 0)
    {
        LCD_SendChar('0');
    }
    else
    {
        LCD_SendChar('5');
    }


    LCD_SendString(" C");
}