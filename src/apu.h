#ifndef APU_H
#define APU_H

#include "stdint.h"

class APU
{
private:
    uint8_t APU_PULSE_1[4];    // 0x4000 - 0x4003
    uint8_t APU_PULSE_2[4];    // 0x4004 - 0x4007
    uint8_t APU_TRIANGLE[4];   // 0x4008 - 0x400B
    uint8_t APU_NOISE[4];      // 0x400C - 0x400F
    uint8_t APU_DMC[4];        // 0x4010 - 0x4013
    uint8_t APU_STATUS;        // 0x4015
    uint8_t APU_FRAME_COUNTER; // 0x4017

public:
    APU();
    void writeRegister(uint16_t address, uint8_t value);
};

#endif