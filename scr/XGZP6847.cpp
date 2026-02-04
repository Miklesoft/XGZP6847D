#include "XGZP6847.h"

XGZP6847::XGZP6847(uint8_t i2c_addr, uint8_t sda, uint8_t scl)
    : _addr(i2c_addr), _sda(sda), _scl(scl) {}

void XGZP6847::begin() {
    Wire.begin(_sda, _scl);
    Wire.setClock(100000);
}

uint8_t XGZP6847::readReg8(uint8_t reg) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return 0xFF;
    Wire.requestFrom(_addr, (uint8_t)1);
    return Wire.available() ? Wire.read() : 0xFF;
}

bool XGZP6847::writeReg8(uint8_t reg, uint8_t val) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.write(val);
    return (Wire.endTransmission() == 0);
}

void XGZP6847::startMeasurement() {
    writeReg8(REG_CMD, 0x0A);
}

bool XGZP6847::measurementFinished() {
    uint8_t cmd = readReg8(REG_CMD);
    return ((cmd & (1 << 3)) == 0);
}

int32_t XGZP6847::readPressureRaw() {
    uint32_t raw =
        ((uint32_t)readReg8(REG_PRESS_MSB) << 16) |
        ((uint32_t)readReg8(REG_PRESS_CSB) << 8)  |
         (uint32_t)readReg8(REG_PRESS_LSB);

    if (raw & 0x800000) {
        return (int32_t)(raw - (1UL << 24));
    } else {
        return (int32_t)raw;
    }
}

int16_t XGZP6847::readTemperatureRaw() {
    uint16_t raw = ((uint16_t)readReg8(REG_TEMP_MSB) << 8) |
                    (uint16_t)readReg8(REG_TEMP_LSB);

    if (raw < 0x8000) return (int16_t)raw;
    else return (int16_t)(raw - 0x10000);
}

float XGZP6847::readPressureBar() {
    int32_t raw = readPressureRaw();
    float pressurePa = raw / K_FACTOR;
    return pressurePa * PA_TO_BAR;
}

float XGZP6847::readTemperatureC() {
    int16_t raw = readTemperatureRaw();
    return raw / 256.0;
}

