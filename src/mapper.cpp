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

uint8_t Mapper::read8(uint16_t address, vector<uint8_t> &prgRom)
{
    ReadResult mapResult = mapperFormat->read8(address);
    switch (mapResult.resultDestination)
    {
    case ResultDestination::PRG:
        return prgRom[mapResult.resultAddress];
    case ResultDestination::UNKNOWN:
    default:
        cout << "Address at (0x" << hex << (int)mapResult.resultAddress << ") was unidentified. Unable to map." << endl;
        return 0;
    }
}