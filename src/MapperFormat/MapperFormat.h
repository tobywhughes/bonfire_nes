#ifndef MAPPER_FORMAT_H
#define MAPPER_FORMAT_H

#include <string>

class MapperFormat
{
public:
    virtual ~MapperFormat(){};
    virtual std::string getFormatName() = 0;
    virtual uint16_t readPrgAddress(uint16_t address) = 0;
    virtual void initialize(uint8_t prgRomSize) = 0;
};

#endif