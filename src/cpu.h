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
    JUMP_ABSOLUTE_SAVE_RETURN = 0x20,
    JUMP_ABSOLUTE = 0x4C,
    SET_INTERRUPT_DISABLE = 0x78,
    STORE_ACCUMULATOR_AT_ABSOLUTE = 0x8D,
    STORE_INDEX_X_AT_ABSOLUTE = 0x8E,
    TRANSFER_INDEX_X_TO_STACK_POINTER = 0x9A,
    LOAD_INDEX_Y_WITH_IMMEDIATE = 0xA0,
    LOAD_INDEX_X_WITH_IMMEDIATE = 0xA2,
    LOAD_ACCUMULATOR_WITH_IMMEDIATE = 0xA9,
    CLEAR_DECIMAL_MODE = 0xD8,
    INCREMENT_INDEX_X = 0xE8,
    STORE_INDEX_Y_AT_ZERO_PAGE = 0x84,
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
    void clearDecimalMode();
    void jumpAbsolute(Memory &memory);
    void printVerbose(std::string verboseString);
    void storeAccumulatorAtAbsolute(Memory &memory);
    void loadAccumulatorWithImmediate(Memory &memory);
    void loadXIndexWithImmediate(Memory &memory);
    void loadIndexYWithImmediate(Memory &memory);
    void transferIndexXToStackPointer();
    void incrementIndexX();
    void storeIndexXAtAbsolute(Memory &memory);
    void jumpAbsoluteSaveReturn(Memory &memory);
    void storeIndexYAtZeroPage(Memory &memory);

public:
    CPU();
    void initialize(Memory &memory);
    void execute(Memory &memory);
};

#endif