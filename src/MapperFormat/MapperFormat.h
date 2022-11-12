#ifndef MAPPER_FORMAT_H
#define MAPPER_FORMAT_H

#include <string>

class MapperFormat
{
public:
    virtual ~MapperFormat(){};
    virtual std::string getFormatName() = 0;
};

#endif