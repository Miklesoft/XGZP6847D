#pragma once
#include <Arduino.h>
#include <Wire.h>

class XGZP6847 {
public:
    XGZP6847(uint8_t i2c_addr = 0x6D, uint8_t sda = 21, uint8_t scl = 22);

    void begin();
    void startMeasurement();
    bool measurementFinished();

    int32_t readPressureRaw();
    int16_t readTemperatureRaw();

    float readPressureBar();
    float readTemperatureC();

private:
    uint8_t _addr;
    uint8_t _sda;
    uint8_t _scl;

    // Register
    static constexpr uint8_t REG_PRESS_MSB = 0x06;
    static constexpr uint8_t REG_PRESS_CSB = 0x07;
    static constexpr uint8_t REG_PRESS_LSB = 0x08;
    static constexpr uint8_t REG_TEMP_MSB  = 0x09;
    static constexpr uint8_t REG_TEMP_LSB  = 0x0A;
    static constexpr uint8_t REG_CMD       = 0x30;

    uint8_t readReg8(uint8_t reg);
    bool writeReg8(uint8_t reg, uint8_t val);

    static constexpr float K_FACTOR = 8.0;      // laut Datenblatt
    static constexpr float PA_TO_BAR = 1e-5;
};
