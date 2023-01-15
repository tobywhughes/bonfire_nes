#include <iostream>
#include "ppu.h"
#include "terminal.h"

using namespace std;

PPU::PPU()
{
}

void PPU::writeRegister(uint16_t address, uint8_t value)
{

    switch (address)
    {
    case 0x2000:
        PPU_CTRL = value;
        break;
    case 0x2001:
        PPU_MASK = value;
        break;
    case 0x2002:
        PPU_STATUS = value;
        break;
    case 0x2003:
        OAM_ADDR = value;
        break;
    case 0x2004:
        OAM_DATA = value;
        break;
    case 0x2005:
        PPU_SCROLL = value;
        break;
    case 0x2006:
        PPU_ADDR = value;
        break;
    case 0x2007:
        PPU_DATA = value;
        break;
    case 0x4014:
        OAM_DMA = value;
        break;
    default:
        cout << T_WARNING << "Address {0x" << hex << (int)address << "} not mapped to PPU - Mapper Error";
    }
}

uint8_t PPU::readRegister(uint16_t address)
{

    switch (address)
    {
    case 0x2000:
        return PPU_CTRL;
    case 0x2001:
        return PPU_MASK;
    case 0x2002:
        return PPU_STATUS;
    case 0x2003:
        return OAM_ADDR;
    case 0x2004:
        return OAM_DATA;
    case 0x2005:
        return PPU_SCROLL;
    case 0x2006:
        return PPU_ADDR;
    case 0x2007:
        return PPU_DATA;
    case 0x4014:
        return OAM_DMA;
    default:
        cout << T_ERROR << "Address {0x" << hex << (int)address << "} not mapped to PPU - Mapper Error";
        exit(0);
    }
}
