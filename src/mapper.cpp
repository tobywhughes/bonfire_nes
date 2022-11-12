#include <iostream>
#include "mapper.h"

using namespace std;

Mapper::Mapper(){

};

void Mapper::detectMapperNumber(uint8_t lowerFlag, uint8_t upperFlag)
{
    mapperNumber = (lowerFlag >> 4) | (upperFlag & 0xF0);
    setMapperFormat();
    cout << "Mapper Format: " << mapperFormat->getFormatName() << endl;
    // std::cout << "Mapper number: " << mapperTypeName(mapperNumber) << std::endl;
};

void Mapper::setMapperFormat()
{
    switch (static_cast<MapperType>(mapperNumber))
    {
    case MapperType::NROM:
        mapperFormat = new NROM();
        break;
    default:
        cout << "Unimplemented Mapper. Exiting" << endl;
        exit(0);
    }
}