#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <string>
#include "memory.h"
#include "enums/opcode.h"

const uint16_t RESET_VECTOR_ADDRESS = 0xFFFC;
const uint8_t POWER_UP_STATUS_REGISTER = 0x34;
const uint8_t POWER_UP_STACK_POINTER = 0xFD;
const uint8_t POWER_UP_STATUS_ACCUMULATOR = 0x00;
const uint8_t POWER_UP_STATUS_X_INDEX = 0x00;
const uint8_t POWER_UP_STATUS_Y_INDEX = 0x00;

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

    // status Register
    void status_setNegative(bool value);
    void status_setOverflow(bool value);
    void status_setBreak(bool value);
    void status_setDecimal(bool value);
    void status_setInterrupt(bool value);
    void status_setZero(bool value);
    void status_setCarry(bool value);
    bool status_getNegative();
    bool status_getOverflow();
    bool status_getBreak();
    bool status_getDecimal();
    bool status_getInterrupt();
    bool status_getZero();
    bool status_getCarry();

    void setInterruptDisable();
    void clearDecimalMode();
    void jumpAbsolute(Memory &memory);
    void printVerbose(std::string verboseString);
    void storeAccumulatorAtAbsolute(Memory &memory);
    void storeAccumulatorAtAbsoluteXIndexed(Memory &memory);
    void loadAccumulatorWithImmediate(Memory &memory);
    void loadXIndexWithImmediate(Memory &memory);
    void loadIndexYWithImmediate(Memory &memory);
    void transferIndexXToStackPointer();
    void transferAccumulatorToIndexX();
    void transferAccumulatorToIndexY();
    void transferStackPointerToIndexX();
    void transferIndexYToAccumulator();
    void incrementIndexX();
    void decrementIndexX();
    void decrementIndexY();
    void storeIndexXAtAbsolute(Memory &memory);
    void jumpAbsoluteSaveReturn(Memory &memory);
    void storeIndexYAtZeroPage(Memory &memory);
    void storeIndexXAtZeroPage(Memory &memory);
    void storeAccumulatorAtZeroPage(Memory &memory);
    void storeAccumulatorAtIndirectYIndexed(Memory &memory);
    void storeAccumulatorAtZeroPageXIndex(Memory &memory);
    void incrementIndexY();
    void branchOnZeroClear(Memory &memory);
    void branchOnNegativeSet(Memory &memory);
    void branchOnNegativeClear(Memory &memory);
    void incrementZeroPagedAddress(Memory &memory);
    void returnFromSubroutine(Memory &memory);
    void absoluteBitwiseTest(Memory &memory);
    void orMemoryWithAccumulatorAbsolute(Memory &memory);
    void pushAccumulatorToStack(Memory &memory);
    void pullAccumulatorFromStack(Memory &memory);
    void pullStatusFromStack(Memory &memory);

public:
    CPU();
    void initialize(Memory &memory);
    void execute(Memory &memory, unsigned long int opcodesExecuted);
};

#endif