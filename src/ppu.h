#ifndef PPU_H
#define PPU_H

#include "stdint.h"

class PPU
{
private:
    uint8_t PPU_CTRL;   // 0x2000
    uint8_t PPU_MASK;   // 0x2001
    uint8_t PPU_STATUS; // 0x2002
    uint8_t OAM_ADDR;   // 0x2003
    uint8_t OAM_DATA;   // 0x2004
    uint8_t PPU_SCROLL; // 0x2005
    uint8_t PPU_ADDR;   // 0x2006
    uint8_t PPU_DATA;   // 0x2007
    uint8_t OAM_DMA;    // 0x4014

public:
    PPU();
    void writeRegister(uint16_t address, uint8_t value);
};

#endif