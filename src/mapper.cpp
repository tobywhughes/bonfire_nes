#include <iostream>
#include "mapper.h"
#include "terminal.h"

using namespace std;

Mapper::Mapper(){

};

void Mapper::detectMapperNumber(uint8_t lowerFlag, uint8_t upperFlag, uint8_t prgRomSize)
{
    mapperNumber = (lowerFlag >> 4) | (upperFlag & 0xF0);
    setMapperFormat(prgRomSize);
    cout << T_INFO << "Mapper Format: " << mapperFormat->getFormatName() << endl;
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
        cout << T_ERROR << "Unimplemented Mapper. Exiting" << endl;
        exit(0);
    }
}

uint8_t Mapper::read8(uint16_t address, vector<uint8_t> &prgRom, vector<uint8_t> &internalRam, PPU ppu)
{
    ReadResult mapResult = mapperFormat->read(address);
    switch (mapResult.resultDestination)
    {
    case ResultDestination::PRG:
        return prgRom[mapResult.resultAddress];
    case ResultDestination::INTERNAL_RAM:
        return internalRam[mapResult.resultAddress];
    case ResultDestination::PPU_DATA:
        return ppu.readRegister(mapResult.resultAddress);
    case ResultDestination::UNKNOWN:
    default:
        cout << T_WARNING << "Address at {0x" << hex << (int)mapResult.resultAddress << "} is unmapped - Unable to read" << endl;
        return 0;
    }
}

uint16_t Mapper::read16(uint16_t address, vector<uint8_t> &prgRom, vector<uint8_t> &internalRam)

{
    uint16_t higher;
    uint16_t lower;

    ReadResult mapResult = mapperFormat->read(address);
    switch (mapResult.resultDestination)
    {
    case ResultDestination::PRG:
        return (uint16_t)prgRom[mapResult.resultAddress] | ((uint16_t)prgRom[mapResult.resultAddress + 1] << 8);
    case ResultDestination::INTERNAL_RAM:
        return (uint16_t)internalRam[mapResult.resultAddress] | ((uint16_t)internalRam[mapResult.resultAddress + 1] << 8);
    case ResultDestination::UNKNOWN:
    default:
        cout << T_WARNING << "Address at {0x" << hex << (int)mapResult.resultAddress << "} is unmapped - Unable to read" << endl;
        return 0;
    }
}

void Mapper::write8(uint16_t address, uint8_t value, vector<uint8_t> &internalRam, PPU ppu, vector<uint8_t> &prgRam, APU apu)
{
    if (address < 0x800)
    {
        internalRam[address] = value;
    }
    else if ((address >= 0x2000 && address <= 0x2007) || address == 0x4014)
    {
        ppu.writeRegister(address, value);
    }
    else if (address >= 0x4000 && address < 0x4020)
    {
        apu.writeRegister(address, value);
    }

    // Temporary Implementation for NES Test Rom Functionality
    // NROM 0 this is mostly unused except in Family Basic
    // But NES Test Roms Use This To Write Results
    else if (address >= 0x6000 && address < 0x8000)
    {
        prgRam[address - 0x6000] = value;
        // Again, more temporary test runner code
        // 0x6000 used as status bit for testing
        if (address == 0x6000)
        {
            if (value == 0x80)
            {
                cout << T_INFO << "NES Test Rom - Tests Running" << endl;
            }
            else if (value == 0x81)
            {
                cout << T_WARNING << "NES Test Rom - Requires Reset" << endl;
            }
            else if (value < 0x80)
            {
                cout << T_INFO << "NES Test Rom - Test 0x" << hex << int(value) << " Completed" << endl;
            }
        }
    }
    else
    {
        cout << T_WARNING << "Address at {0x" << hex << (int)address << "} is unmapped - Unable to set value: 0x" << hex << (int)value << endl;
    }
}
