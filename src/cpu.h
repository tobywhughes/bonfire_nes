#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <string>
#include "memory.h"

const uint16_t RESET_VECTOR_ADDRESS = 0xFFFC;
const uint8_t POWER_UP_STATUS_REGISTER = 0x34;
const uint8_t POWER_UP_STACK_POINTER = 0xFD;
const uint8_t POWER_UP_STATUS_ACCUMULATOR = 0x00;
const uint8_t POWER_UP_STATUS_X_INDEX = 0x00;
const uint8_t POWER_UP_STATUS_Y_INDEX = 0x00;

enum Opcode
{
    JUMP_ABSOLUTE = 0x4C,
    SET_INTERRUPT_DISABLE = 0x78,
    UNKNOWN_OPCODE,
};

class CPU
{
private:
    uint16_t m_programCounter; // PC
    uint8_t m_accumulator;     // A
    uint8_t m_xIndex;          // X
    uint8_t m_yIndex;          // Y
    uint8_t m_stackPointer;    // S
    uint8_t m_statusRegister;  // P

    void opcodeDebugOutput(uint8_t opcode);

    void setInterruptDisable();
    void jumpAbsolute(Memory &memory);
    void printVerbose(std::string verboseString);

public:
    CPU();
    void initialize(Memory &memory);
    void execute(Memory &memory);
};

#endif