#include <iostream>
#include "mapper.h"

using namespace std;

Mapper::Mapper(){

};

void Mapper::detectMapperNumber(uint8_t lowerFlag, uint8_t upperFlag, uint8_t prgRomSize)
{
    mapperNumber = (lowerFlag >> 4) | (upperFlag & 0xF0);
    setMapperFormat(prgRomSize);
    cout << "Mapper Format: " << mapperFormat->getFormatName() << endl;
    // std::cout << "Mapper number: " << mapperTypeName(mapperNumber) << std::endl;
};

void Mapper::setMapperFormat(uint8_t prgRomSize)
{
    switch (static_cast<MapperType>(mapperNumber))
    {
    case MapperType::NROM:
        mapperFormat = new NROM();
        mapperFormat->initialize(prgRomSize);
        break;
    default:
        cout << "Unimplemented Mapper. Exiting" << endl;
        exit(0);
    }
}

uint16_t Mapper::readPrgAddress(uint16_t address)
{
    return mapperFormat->readPrgAddress(address);
}