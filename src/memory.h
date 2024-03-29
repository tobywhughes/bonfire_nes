#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include "mapper.h"
#include "ppu.h"
#include "rom.h"
#include "apu.h"

class Memory
{
private:
    Mapper m_mapper;
    Rom m_rom;
    PPU m_ppu;
    APU m_apu;

    std::vector<uint8_t> m_internalRAM; // 2KB - 0x800

public:
    Memory(std::string fileName);
    uint8_t read8(uint16_t address);
    uint16_t read16(uint16_t address);
    void write8(uint16_t address, uint8_t value);
};

#endif