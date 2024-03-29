#include "memory.h"

using namespace std;

Memory::Memory(string fileName) : m_rom(fileName), m_internalRAM(0x800, 0), m_ppu(), m_apu()
{
    m_rom.initialize(m_mapper);
}

uint8_t Memory::read8(uint16_t address)
{
    return m_mapper.read8(address, m_rom.prgRom, m_internalRAM, m_ppu);
}

uint16_t Memory::read16(uint16_t address)
{
    return m_mapper.read16(address, m_rom.prgRom, m_internalRAM);
}

void Memory::write8(uint16_t address, uint8_t value)
{
    m_mapper.write8(address, value, m_internalRAM, m_ppu, m_rom.prgRam, m_apu);
}
