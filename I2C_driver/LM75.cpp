#include "LM75.h"
#include "I2C.h"


void LM75_Init(void)
{
    // LM75 uses its default configuration.
    // No configuration is required for basic temperature reading.
}


int16_t LM75_ReadTemperature_x2(void)
{
    unsigned char temperature_MSB;
    unsigned char temperature_LSB;

    int16_t raw_temperature;


    // =========================
    // 1. START
    // =========================
    I2C_Start();


    // =========================
    // 2. Send LM75 address + WRITE
    // =========================
    I2C_Write((LM75_ADDRESS << 1) | 0);


    // =========================
    // 3. Select Temperature Register
    // =========================
    I2C_Write(0x00);


    // =========================
    // 4. Repeated START
    // =========================
    I2C_Start();


    // =========================
    // 5. Send LM75 address + READ
    // =========================
    I2C_Write((LM75_ADDRESS << 1) | 1);


    // =========================
    // 6. Read MSB
    // =========================
    temperature_MSB = I2C_Read_ACK();


    // =========================
    // 7. Read LSB
    // =========================
    temperature_LSB = I2C_Read_NACK();


    // =========================
    // 8. STOP
    // =========================
    I2C_Stop();


    // =========================
    // 9. Combine the 9-bit data
    // =========================
    raw_temperature =
        ((int16_t)temperature_MSB << 1) |
        (temperature_LSB >> 7);


    // =========================
    // 10. Sign extension
    // =========================
    if (raw_temperature & 0x0100)
    {
        raw_temperature -= 0x0200;
    }


    // Return temperature multiplied by 2
    // Example:
    // 25.0°C  -> 50
    // 25.5°C  -> 51
    // -10.5°C -> -21

    return raw_temperature;
}