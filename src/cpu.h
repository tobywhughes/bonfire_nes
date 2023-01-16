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

    // Opcode Handlers
    void setInterruptDisable();
    void jumpAbsolute(Memory &memory);
    void printVerbose(std::string verboseString);
    void storeAccumulatorAtAbsolute(Memory &memory);
    void storeAccumulatorAtAbsoluteXIndexed(Memory &memory);
    void transferIndexXToStackPointer();
    void transferAccumulatorToIndexX();
    void transferAccumulatorToIndexY();
    void transferStackPointerToIndexX();
    void transferIndexYToAccumulator();
    void incrementIndexX();
    void decrementIndexX();
    void decrementIndexY();
    void jumpAbsoluteSaveReturn(Memory &memory);
    void storeAccumulatorAtZeroPage(Memory &memory);
    void storeAccumulatorAtIndirectYIndexed(Memory &memory);
    void storeAccumulatorAtZeroPageXIndex(Memory &memory);
    void incrementIndexY();
    void incrementZeroPagedAddress(Memory &memory);
    void returnFromSubroutine(Memory &memory);
    void pushAccumulatorToStack(Memory &memory);
    void pullAccumulatorFromStack(Memory &memory);
    void pullStatusFromStack(Memory &memory);
    void pushStatusToStack(Memory &memory);
    void compareWithImmediate(Memory &memory);
    void subractImmediateWithBorrow(Memory &memory);
    void addImmediateWithBorrow(Memory &memory);
    void shiftRightAccumulator();
    void andAccumulatorWithImmediate(Memory &memory);

    // Combined Handlers
    void branchOnStatusRegister(Memory &memory, uint8_t opcode);
    void clearFlag(uint8_t opcode);
    void loadIndexX(Memory &memory, uint8_t opcode);
    void loadIndexY(Memory &memory, uint8_t opcode);
    void storeIndexY(Memory &memory, uint8_t opcode);
    void storeIndexX(Memory &memory, uint8_t opcode);
    void loadAccumulator(Memory &memory, uint8_t opcode);
    void compareIndexX(Memory &memory, uint8_t opcode);
    void compareIndexY(Memory &memory, uint8_t opcode);
    void shiftLeft(Memory &memory, uint8_t opcode);
    void rotateLeft(Memory &memory, uint8_t opcode);
    void orMemoryWithAccumulator(Memory &memory, uint8_t opcode);
    void bitwiseTest(Memory &memory, uint8_t opcode);

    // Memory Helpers
    uint8_t getAbsolute(Memory &memory);
    uint8_t getAbsoluteYIndexed(Memory &memory);
    uint8_t getAbsoluteXIndexed(Memory &memory);
    uint8_t getImmediate(Memory &memory);
    uint8_t getZeroPage(Memory &memory);
    uint8_t getZeroPageXIndexed(Memory &memory);
    uint8_t getZeroPageYIndexed(Memory &memory);
    uint8_t getIndirectYIndexed(Memory &memory);
    uint8_t getIndirectXIndexed(Memory &memory);

    uint16_t getAbsoluteAddress(Memory &memory);
    uint16_t getZeroPageAddress(Memory &memory);
    uint16_t getZeroPageAddressXIndexed(Memory &memory);
    uint16_t getZeroPageAddressYIndexed(Memory &memory);
    uint16_t getIndirectYIndexedAddress(Memory &memory);
    uint16_t getIndirectXIndexedAddress(Memory &memory);

    // Misc Utils
    void setCompareStatus(uint8_t registerValue, uint8_t operand, uint8_t result);
    uint8_t shiftLeftOperation(Memory memory, uint8_t value, bool withCarry, bool setAccumulator, uint16_t destination);

public:
    CPU();
    void initialize(Memory &memory);
    void execute(Memory &memory, unsigned long int opcodesExecuted);
};

#endif