#ifndef DS1302_H
#define DS1302_H

#include <Arduino.h>

class DS1302 {
public:
    DS1302(int clkPin, int dataPin, int rstPin);

    void begin();
    void setTime(uint8_t hour, uint8_t minute, uint8_t second);
    void setDate(uint8_t day, uint8_t month, uint16_t year);
    void getTime(uint8_t& hour, uint8_t& minute, uint8_t& second);
    void getDate(uint8_t& day, uint8_t& month, uint16_t& year);
    void enableClock();
    void disableClock();

    void setTrickleCharge(bool enable, uint8_t diodeCount, uint8_t resistorValue);

private:
    int _clkPin;
    int _dataPin;
    int _rstPin;

    uint8_t bcdToDec(uint8_t bcd);
    uint8_t decToBcd(uint8_t dec);

    void writeByte(uint8_t data);
    uint8_t readByte();
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
};

#endif