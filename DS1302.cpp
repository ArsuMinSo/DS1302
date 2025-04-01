#include "DS1302.h"

DS1302::DS1302(int clkPin, int dataPin, int rstPin)
    : _clkPin(clkPin), _dataPin(dataPin), _rstPin(rstPin) {
}

void DS1302::begin() {
    pinMode(_clkPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    pinMode(_rstPin, OUTPUT);

    digitalWrite(_rstPin, LOW);
    digitalWrite(_clkPin, LOW);

    writeRegister(0x8E, 0x00);

    uint8_t seconds = readRegister(0x80) & 0x7F;
    writeRegister(0x80, seconds);
}

void DS1302::setTime(uint8_t hour, uint8_t minute, uint8_t second) {
    writeRegister(0x80, decToBcd(second) & 0x7F);
    writeRegister(0x82, decToBcd(minute));
    writeRegister(0x84, decToBcd(hour));
}

void DS1302::setDate(uint8_t day, uint8_t month, uint16_t year) {
    writeRegister(0x86, decToBcd(day));
    writeRegister(0x88, decToBcd(month));
    writeRegister(0x8C, decToBcd(year % 100));
}

void DS1302::getTime(uint8_t& hour, uint8_t& minute, uint8_t& second) {
    second = bcdToDec(readRegister(0x81) & 0x7F);
    minute = bcdToDec(readRegister(0x83));
    hour = bcdToDec(readRegister(0x85));
}

void DS1302::getDate(uint8_t& day, uint8_t& month, uint16_t& year) {
    day = bcdToDec(readRegister(0x87));
    month = bcdToDec(readRegister(0x89));
    year = 2000 + bcdToDec(readRegister(0x8D));
}

void DS1302::enableClock() {
    uint8_t seconds = readRegister(0x80) & 0x7F;
    writeRegister(0x80, seconds);
}

void DS1302::disableClock() {
    uint8_t seconds = readRegister(0x80) | 0x80;
    writeRegister(0x80, seconds);
}

void DS1302::setTrickleCharge(bool enable, uint8_t diodeCount, uint8_t resistorValue) {
    uint8_t value = 0x00;

    if (enable) {
        value |= 0xA0;

        if (diodeCount == 1) {
            value |= 0x04;
        }
        else if (diodeCount == 2) {
            value |= 0x08;
        }

        value |= (resistorValue & 0x03);
    }

    writeRegister(0x90, value);
}

uint8_t DS1302::bcdToDec(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t DS1302::decToBcd(uint8_t dec) {
    return ((dec / 10) << 4) | (dec % 10);
}

void DS1302::writeByte(uint8_t data) {
    pinMode(_dataPin, OUTPUT);
    for (int i = 0; i < 8; i++) {
        digitalWrite(_clkPin, LOW);
        digitalWrite(_dataPin, data & 0x01);
        data >>= 1;
        digitalWrite(_clkPin, HIGH);
    }
}

uint8_t DS1302::readByte() {
    uint8_t data = 0;
    pinMode(_dataPin, INPUT);
    for (int i = 0; i < 8; i++) {
        digitalWrite(_clkPin, LOW);
        data |= (digitalRead(_dataPin) << i);
        digitalWrite(_clkPin, HIGH);
    }
    return data;
}

void DS1302::writeRegister(uint8_t reg, uint8_t value) {
    digitalWrite(_rstPin, HIGH);
    writeByte(reg);
    writeByte(value);
    digitalWrite(_rstPin, LOW);
}

uint8_t DS1302::readRegister(uint8_t reg) {
    uint8_t value;
    digitalWrite(_rstPin, HIGH);
    writeByte(reg | 0x01);
    value = readByte();
    digitalWrite(_rstPin, LOW);
    return value;
}
