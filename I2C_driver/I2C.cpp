#include "I2C.h"

void I2C_Init(void)
{
    // Set I2C prescaler to 1
    TWSR = 0x00;

    // Set I2C clock frequency
    TWBR = 32;

    // Enable TWI
    TWCR = (1 << TWEN);
}


void I2C_Start(void)
{
    // Send START condition
    TWCR = (1 << TWINT) |
           (1 << TWSTA) |
           (1 << TWEN);

    // Wait until START condition is transmitted
    while (!(TWCR & (1 << TWINT)));
}


void I2C_Stop(void)
{
    // Send STOP condition
    TWCR = (1 << TWINT) |
           (1 << TWSTO) |
           (1 << TWEN);
}


void I2C_Write(unsigned char data)
{
    // Put data into TWI Data Register
    TWDR = data;

    // Start data transmission
    TWCR = (1 << TWINT) |
           (1 << TWEN);

    // Wait until transmission is complete
    while (!(TWCR & (1 << TWINT)));
}


unsigned char I2C_Read_ACK(void)
{
    // Receive data and send ACK
    TWCR = (1 << TWINT) |
           (1 << TWEA) |
           (1 << TWEN);

    // Wait until data is received
    while (!(TWCR & (1 << TWINT)));

    // Return received data
    return TWDR;
}


unsigned char I2C_Read_NACK(void)
{
    // Receive data without sending ACK
    TWCR = (1 << TWINT) |
           (1 << TWEN);

    // Wait until data is received
    while (!(TWCR & (1 << TWINT)));

    // Return received data
    return TWDR;
}