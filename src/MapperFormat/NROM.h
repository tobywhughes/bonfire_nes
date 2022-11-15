#ifndef NROM_H
#define NROM_H

#include "MapperFormat.h"
#include <string>

class NROM : public MapperFormat
{
private:
    uint8_t m_prgRomSize;
    uint16_t readPrgAddress(uint16_t address);

public:
    ~NROM() override = default;
    std::string getFormatName() override;
    ReadResult read8(uint16_t address) override;
    void initialize(uint8_t prgRomSize) override;
};

#endif