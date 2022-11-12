#ifndef NROM_H
#define NROM_H

#include "MapperFormat.h"
#include <string>

class NROM : public MapperFormat
{
public:
    NROM(){};
    ~NROM() override = default;
    std::string getFormatName() override;
};

#endif