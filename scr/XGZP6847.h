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
//  The K value is selected according to the positive pressure value only.
//  Positive Pressure Range (kPa)	K Value
//  500 < P ≤ 1000	               8
//  260 < P ≤ 500	                16
//  130 < P ≤ 260	                32
//  65 < P ≤ 130	                64
//  32 < P ≤ 65	                  128
//  16 < P ≤ 32	                  256
//  8 < P ≤ 16	                  512
//  4 < P ≤ 8	                   1024
//  2 ≤ P ≤ 4	                   2048
//  1 ≤ P < 2	                   4096

    static constexpr float PA_TO_BAR = 1e-5;
};

