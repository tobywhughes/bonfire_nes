#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>
#include <string>
#include <vector>

#include "MapperFormat/MapperFormat.h"
#include "MapperFormat/NROM.h"
#include "ppu.h"

enum class MapperType : uint8_t
{
    NROM = 0x00,
};

class Mapper
{
private:
    uint8_t mapperNumber;
    MapperFormat *mapperFormat;
    void setMapperFormat(uint8_t prgRomSize);

public:
    Mapper();
    void detectMapperNumber(uint8_t lowerFlag, uint8_t upperFlag, uint8_t prgRomSize);
    uint8_t read8(uint16_t address, std::vector<uint8_t> &prgRom);
    uint16_t read16(uint16_t address, std::vector<uint8_t> &prgRom);
    void write8(uint16_t address, uint8_t value, std::vector<uint8_t> &internalRam, PPU ppu);
};

#endif