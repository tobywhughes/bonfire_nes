#ifndef DEBUG_H
#define DEBUG_H

#include <string>

class Debug
{
public:
    static void opcodeDebugOutput(uint8_t opcode, uint16_t programCounter, bool printDebug);
};

#endif