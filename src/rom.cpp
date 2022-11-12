#include "rom.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Rom::Rom(string fileName)
{
    cout << "ROM Filename: " << fileName << endl;
    ifstream file(fileName, ios::binary);
    buffer = vector<uint8_t>(istreambuf_iterator<char>(file), {});
    file.close();
}

void Rom::initialize(Mapper &mapper)
{
    readInBootRomHeader(mapper);
}

void Rom::readInBootRomHeader(Mapper &mapper)
{
    copy(buffer.begin(), buffer.begin() + 4, romHeaderData.nameConstant);
    romHeaderData.prgRomSize = buffer[4];
    romHeaderData.chrRomSize = buffer[5];
    romHeaderData.lowerFlag = buffer[6];
    romHeaderData.upperFlag = buffer[7];

    mapper.detectMapperNumber(romHeaderData.lowerFlag, romHeaderData.upperFlag);
}