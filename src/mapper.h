#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>
#include <string>

#include "MapperFormat/MapperFormat.h"
#include "MapperFormat/NROM.h"

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
    uint16_t readPrgAddress(uint16_t address);
};

#endif