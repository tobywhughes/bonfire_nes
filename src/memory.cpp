#include "memory.h"

using namespace std;

Memory::Memory(string fileName) : m_rom(fileName)
{
    m_rom.initialize(m_mapper);
}

uint8_t Memory::read8(uint16_t address)
{
    return m_mapper.read8(address, m_rom.prgRom);
}

uint16_t Memory::read16(uint16_t address)
{
    return m_mapper.read16(address, m_rom.prgRom);
}