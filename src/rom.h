#ifndef ROM_H
#define ROM_H

#include <string>
#include <vector>
#include <stdint.h>
#include "mapper.h"

struct RomHeaderData
{
    uint8_t nameConstant[4];
    uint8_t prgRomSize; // 16KB
    uint8_t chrRomSize; // 8KB
    uint8_t lowerFlag;
    uint8_t upperFlag;
};

class Rom
{
private:
    std::vector<uint8_t> buffer;
    RomHeaderData romHeaderData;

    void readInBootRomHeader(Mapper &mapper);

public:
    Rom(std::string fileName);
    void initialize(Mapper &mapper);
};

#endif