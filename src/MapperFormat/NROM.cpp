#include <iostream>
#include "NROM.h"

using namespace std;

string NROM::getFormatName()
{
    return "NROM - 0x00";
}

ReadResult NROM::read(uint16_t address)
{
    if (address >= 0x8000)
    {
        return ReadResult{
            ResultDestination::PRG,
            readPrgAddress(address)};
    }
    else if (address < 0x0800)
    {
        return ReadResult{
            ResultDestination::INTERNAL_RAM,
            address};
    }
    else
    {
        return ReadResult{
            ResultDestination::UNKNOWN,
            address};
    }
}

uint16_t NROM::readPrgAddress(uint16_t address)
{
    if (m_prgRomSize == 1)
    {
        return (address - 0x8000) & 0xBFFF;
    }
    else
    {
        return address - 0x8000;
    }
}

void NROM::initialize(uint8_t prgRomSize)
{
    m_prgRomSize = prgRomSize;
}