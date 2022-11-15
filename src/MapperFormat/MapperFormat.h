#ifndef MAPPER_FORMAT_H
#define MAPPER_FORMAT_H

#include <string>

enum ResultDestination
{
    PRG,
    UNKNOWN,
};

struct ReadResult
{
    ResultDestination resultDestination;
    uint16_t resultAddress;
};

class MapperFormat
{
public:
    virtual ~MapperFormat(){};
    virtual std::string getFormatName() = 0;
    virtual ReadResult read8(uint16_t address) = 0;
    virtual void initialize(uint8_t prgRomSize) = 0;
};

#endif