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
