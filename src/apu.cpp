#include <iostream>
#include "apu.h"
#include "terminal.h"

using namespace std;

APU::APU()
{
}

void APU::writeRegister(uint16_t address, uint8_t value)
{
    switch (address)
    {
    case 0x4000:
    case 0x4001:
    case 0x4002:
    case 0x4003:
        APU_PULSE_1[address - 0x4000] = value;
        break;
    case 0x4004:
    case 0x4005:
    case 0x4006:
    case 0x4007:
        APU_PULSE_2[address - 0x4000 - 0x4] = value;
        break;
    case 0x4008:
    case 0x4009:
    case 0x400A:
    case 0x400B:
        APU_TRIANGLE[address - 0x4000 - 0x8] = value;
        break;
    case 0x400C:
    case 0x400D:
    case 0x400E:
    case 0x400F:
        APU_NOISE[address - 0x4000 - 0xC] = value;
        break;
    case 0x4010:
    case 0x4011:
    case 0x4012:
    case 0x4013:
        APU_DMC[address - 0x4000 - 0x10] = value;
        break;
    case 0x4015:
        APU_STATUS = value;
        break;
    case 0x4017:
        APU_FRAME_COUNTER = value;
        break;
    default:
        cout << T_WARNING << "Address {0x" << hex << (int)address << "} not mapped to APU - Mapper Error" << endl;
    }
}
