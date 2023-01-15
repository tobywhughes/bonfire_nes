/*
FUTURE TESTING & POSSIBLE DEBUG NOTES:
- Check if C and V flags on ABC and SBC are being set correct
*/

#include <iostream>
#include "cpu.h"
#include "terminal.h"
#include <sstream>
#include <bitset>
#include "Utils/Debug.h"

using namespace std;

const bool PRINT_OPCODE_DEBUG = true;
const bool PRINT_STATUS_DEBUG = false;
const bool PRINT_VERBOSE_OPCODE_DEBUG = PRINT_OPCODE_DEBUG && false;

CPU::CPU()
{
    m_accumulator = POWER_UP_STATUS_ACCUMULATOR;
    m_xIndex = POWER_UP_STATUS_X_INDEX;
    m_yIndex = POWER_UP_STATUS_Y_INDEX;
    m_stackPointer = POWER_UP_STACK_POINTER;
    m_statusRegister = POWER_UP_STATUS_REGISTER;
}

void CPU::initialize(Memory &memory)
{
    m_programCounter = memory.read16(RESET_VECTOR_ADDRESS);
    cout << T_DEBUG << "PC Initialized To: 0x" << hex << (int)m_programCounter << endl;
}

void CPU::execute(Memory &memory, unsigned long int opcodesExecuted)
{
    uint16_t opcode = memory.read8(m_programCounter);
    Debug::opcodeDebugOutput(opcode, m_programCounter, PRINT_OPCODE_DEBUG);

    m_programCounter += 1;

    switch (opcode)
    {
    case Opcode::SET_INTERRUPT_DISABLE:
        setInterruptDisable();
        break;
    case Opcode::CLEAR_INTERRUPT_DISABLE:
    case Opcode::CLEAR_DECIMAL_MODE:
    case Opcode::CLEAR_CARRY_FLAG:
        clearFlag(opcode);
        break;
    case Opcode::JUMP_ABSOLUTE:
        jumpAbsolute(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE:
        storeAccumulatorAtAbsolute(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE_X_INDEXED:
        storeAccumulatorAtAbsoluteXIndexed(memory);
        break;
    case Opcode::TRANSFER_INDEX_X_TO_STACK_POINTER:
        transferIndexXToStackPointer();
        break;
    case Opcode::TRANSFER_ACCUMULATOR_TO_INDEX_X:
        transferAccumulatorToIndexX();
        break;
    case Opcode::TRANSFER_ACCUMULATOR_TO_INDEX_Y:
        transferAccumulatorToIndexY();
        break;
    case Opcode::TRANSFER_STACK_POINTER_TO_INDEX_X:
        transferStackPointerToIndexX();
        break;
    case Opcode::TRANSFER_INDEX_Y_TO_ACCUMULATOR:
        transferIndexYToAccumulator();
        break;
    case Opcode::INCREMENT_INDEX_X:
        incrementIndexX();
        break;
    case Opcode::DECREMENT_INDEX_X:
        decrementIndexX();
        break;
    case Opcode::DECREMENT_INDEX_Y:
        decrementIndexY();
        break;
    case Opcode::INCREMENT_INDEX_Y:
        incrementIndexY();
        break;
    case Opcode::STORE_INDEX_X_AT_ABSOLUTE:
        storeIndexXAtAbsolute(memory);
        break;
    case Opcode::JUMP_ABSOLUTE_SAVE_RETURN:
        jumpAbsoluteSaveReturn(memory);
        break;
    case Opcode::STORE_INDEX_Y_AT_ZERO_PAGE:
        storeIndexYAtZeroPage(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ZERO_PAGE:
        storeAccumulatorAtZeroPage(memory);
        break;
    case Opcode::STORE_INDEX_X_AT_ZERO_PAGE:
        storeIndexXAtZeroPage(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_INDIRECT_Y_INDEXED:
        storeAccumulatorAtIndirectYIndexed(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ZEROPAGE_X_INDEXED:
        storeAccumulatorAtZeroPageXIndex(memory);
        break;
    case Opcode::BRANCH_ON_ZERO_CLEAR:
    case Opcode::BRANCH_ON_ZERO_SET:
    case Opcode::BRANCH_ON_NEGATIVE_CLEAR:
    case Opcode::BRANCH_ON_NEGATIVE_SET:
    case Opcode::BRANCH_ON_CARRY_CLEAR:
    case Opcode::BRANCH_ON_CARRY_SET:
    case Opcode::BRANCH_ON_OVERFLOW_CLEAR:
    case Opcode::BRANCH_ON_OVERFLOW_SET:
        branchOnStatusRegister(memory, opcode);
        break;
    case Opcode::INCREMENT_ZERO_PAGED_ADDRESS:
        incrementZeroPagedAddress(memory);
        break;
    case Opcode::RETURN_FROM_SUBROUTINE:
        returnFromSubroutine(memory);
        break;
    case Opcode::ABSOLUTE_BITWISE_TEST:
        absoluteBitwiseTest(memory);
        break;
    case Opcode::OR_MEMORY_WITH_ACCUMULATOR_ABSOLUTE:
        orMemoryWithAccumulatorAbsolute(memory);
        break;
    case Opcode::PUSH_ACCUMULATOR_TO_STACK:
        pushAccumulatorToStack(memory);
        break;
    case Opcode::PULL_ACCUMULATOR_FROM_STACK:
        pullAccumulatorFromStack(memory);
        break;
    case Opcode::PULL_STATUS_FROM_STACK:
        pullStatusFromStack(memory);
        break;
    case Opcode::PUSH_STATUS_TO_STACK:
        pushStatusToStack(memory);
        break;
    case Opcode::COMPARE_WITH_IMMEDIATE:
        compareWithImmediate(memory);
        break;
    case Opcode::SUBRACT_IMMEDIATE_WITH_BORROW:
        subractImmediateWithBorrow(memory);
        break;
    case Opcode::ADD_IMMEDIATE_WITH_BORROW:
        addImmediateWithBorrow(memory);
        break;
    case Opcode::SHIFT_RIGHT_ACCUMULATOR:
        shiftRightAccumulator();
        break;
    case Opcode::AND_ACCUMULATOR_WITH_IMMEDIATE:
        andAccumulatorWithImmediate(memory);
        break;
    case Opcode::LOAD_INDEX_X_WITH_ABSOLUTE:
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
    case Opcode::LOAD_INDEX_X_WITH_ZERO_PAGE:
    case Opcode::LOAD_INDEX_X_ZERO_PAGE_Y_INDEXED:
    case Opcode::LOAD_INDEX_X_WITH_ABSOLUTE_Y_INDEXED:
        loadIndexX(memory, opcode);
        break;
    case Opcode::LOAD_INDEX_Y_WITH_ABSOLUTE:
    case Opcode::LOAD_INDEX_Y_WITH_IMMEDIATE:
    case Opcode::LOAD_INDEX_Y_WITH_ZERO_PAGE:
    case Opcode::LOAD_INDEX_Y_ZERO_PAGE_X_INDEXED:
    case Opcode::LOAD_INDEX_Y_WITH_ABSOLUTE_X_INDEXED:
        loadIndexY(memory, opcode);
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE:
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
    case Opcode::LOAD_ACCUMULATOR_WITH_ZERO_PAGE:
    case Opcode::LOAD_ACCUMULATOR_ZERO_PAGE_X_INDEXED:
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE_X_INDEXED:
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE_Y_INDEXED:
        loadAccumulator(memory, opcode);
        break;
    case Opcode::COMPARE_IMMEDIATE_AND_INDEX_X:
    case Opcode::COMPARE_ABSOLUTE_AND_INDEX_X:
    case Opcode::COMPARE_ZERO_PAGE_AND_INDEX_X:
        compareIndexX(memory, opcode);
        break;
    case Opcode::COMPARE_IMMEDIATE_AND_INDEX_Y:
    case Opcode::COMPARE_ABSOLUTE_AND_INDEX_Y:
    case Opcode::COMPARE_ZERO_PAGE_AND_INDEX_Y:
        compareIndexY(memory, opcode);
        break;
    case Opcode::UNKNOWN_OPCODE:
    default:
        cout << T_ERROR << "Unimplemented Opcode: 0x" << hex << (int)opcode << endl;
        cout << T_DEBUG << "Opcodes Executed - " << dec << opcodesExecuted << endl;
        cout << T_ERROR << "Exiting Program" << endl;
        exit(0);
        break;
    }
}

void CPU::setInterruptDisable()
{
    status_setInterrupt(true);

    ostringstream verboseString;
    verboseString << "Status Register Updated: 0b" << bitset<8>(m_statusRegister);
    printVerbose(verboseString.str());
}

void CPU::jumpAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);

    ostringstream verboseString;
    verboseString << "Jump to {0x" << hex << int(absoluteAddress) << "}";
    printVerbose(verboseString.str());

    m_programCounter = absoluteAddress;
}

void CPU::storeAccumulatorAtAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    memory.write8(absoluteAddress, m_accumulator);

    ostringstream verboseString;
    verboseString << "Storing Accumulator value 0x" << hex << int(m_accumulator) << " at address {0x" << hex << int(absoluteAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeAccumulatorAtAbsoluteXIndexed(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);

    m_programCounter += 2;

    absoluteAddress += m_xIndex;

    memory.write8(absoluteAddress, m_accumulator);

    ostringstream verboseString;
    verboseString << "Storing Accumulator value 0x" << hex << int(m_accumulator) << " at address {0x" << hex << int(absoluteAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeIndexYAtZeroPage(Memory &memory)
{
    uint8_t address = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint16_t zeroPagedAddress = 0x0000 | address;

    memory.write8(zeroPagedAddress, m_yIndex);

    ostringstream verboseString;
    verboseString << "Storing Index Y value 0x" << hex << int(m_yIndex) << " at zero page address {0x" << hex << int(zeroPagedAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeAccumulatorAtIndirectYIndexed(Memory &memory)
{
    uint8_t operand = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint16_t zeroPagedInitialLookupAddress = 0x0000 | operand;

    uint16_t lookupValue = memory.read16(zeroPagedInitialLookupAddress);
    uint8_t lookupValueLow = (uint8_t)(0x00FF & lookupValue);

    lookupValue &= 0xFF00;
    lookupValueLow += m_yIndex;

    lookupValue |= lookupValueLow;

    memory.write8(lookupValue, m_accumulator);

    ostringstream verboseString;
    verboseString << "Storing Accumulator value 0x" << hex << int(m_accumulator) << " at address {0x" << hex << int(lookupValue) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeAccumulatorAtZeroPageXIndex(Memory &memory)
{
    uint8_t operand = memory.read8(m_programCounter);
    m_programCounter += 1;

    operand += m_xIndex;

    memory.write8((uint16_t)operand, m_accumulator);

    ostringstream verboseString;
    verboseString << "Storing Accumulator value 0x" << hex << int(m_accumulator) << " at address {0x" << hex << int((uint16_t)operand) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeIndexXAtZeroPage(Memory &memory)
{
    uint8_t address = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint16_t zeroPagedAddress = 0x0000 | address;

    memory.write8(zeroPagedAddress, m_xIndex);

    ostringstream verboseString;
    verboseString << "Storing Index X value 0x" << hex << int(m_xIndex) << " at zero page address {0x" << hex << int(zeroPagedAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeAccumulatorAtZeroPage(Memory &memory)
{
    uint8_t address = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint16_t zeroPagedAddress = 0x0000 | address;

    memory.write8(zeroPagedAddress, m_accumulator);

    ostringstream verboseString;
    verboseString << "Storing Index X value 0x" << hex << int(m_accumulator) << " at zero page address {0x" << hex << int(zeroPagedAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::storeIndexXAtAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    memory.write8(absoluteAddress, m_xIndex);

    ostringstream verboseString;
    verboseString << "Storing Index X value 0x" << hex << int(m_xIndex) << " at address {0x" << hex << int(absoluteAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::loadIndexX(Memory &memory, uint8_t opcode)
{
    uint8_t resultValue;

    switch (opcode)
    {
    case Opcode::LOAD_INDEX_X_WITH_ABSOLUTE:
        resultValue = getAbsolute(memory);
        break;
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
        resultValue = getImmediate(memory);
        break;
    case Opcode::LOAD_INDEX_X_WITH_ZERO_PAGE:
        resultValue = getZeroPage(memory);
        break;
    case Opcode::LOAD_INDEX_X_ZERO_PAGE_Y_INDEXED:
        resultValue = getZeroPageYIndexed(memory);
        break;
    case Opcode::LOAD_INDEX_X_WITH_ABSOLUTE_Y_INDEXED:
        resultValue = getAbsoluteYIndexed(memory);
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - LDX Called Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    m_xIndex = resultValue;

    status_setNegative((m_xIndex & 0b10000000) != 0);
    status_setZero(m_xIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading X Index with value 0x" << hex << int(resultValue);
    printVerbose(verboseString.str());
}

void CPU::loadIndexY(Memory &memory, uint8_t opcode)
{
    uint8_t resultValue;

    switch (opcode)
    {
    case Opcode::LOAD_INDEX_Y_WITH_ABSOLUTE:
        resultValue = getAbsolute(memory);
        break;
    case Opcode::LOAD_INDEX_Y_WITH_IMMEDIATE:
        resultValue = getImmediate(memory);
        break;
    case Opcode::LOAD_INDEX_Y_WITH_ZERO_PAGE:
        resultValue = getZeroPage(memory);
        break;
    case Opcode::LOAD_INDEX_Y_ZERO_PAGE_X_INDEXED:
        resultValue = getZeroPageXIndexed(memory);
        break;
    case Opcode::LOAD_INDEX_Y_WITH_ABSOLUTE_X_INDEXED:
        resultValue = getAbsoluteXIndexed(memory);
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - LDY Called On Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    m_yIndex = resultValue;

    status_setNegative((m_yIndex & 0b10000000) != 0);
    status_setZero(m_yIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading Y Index with value 0x" << hex << int(resultValue);
    printVerbose(verboseString.str());
}

void CPU::loadAccumulator(Memory &memory, uint8_t opcode)
{
    uint8_t resultValue;

    switch (opcode)
    {
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE:
        resultValue = getAbsolute(memory);
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
        resultValue = getImmediate(memory);
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ZERO_PAGE:
        resultValue = getZeroPage(memory);
        break;
    case Opcode::LOAD_ACCUMULATOR_ZERO_PAGE_X_INDEXED:
        resultValue = getZeroPageXIndexed(memory);
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE_X_INDEXED:
        resultValue = getAbsoluteXIndexed(memory);
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE_Y_INDEXED:
        resultValue = getAbsoluteYIndexed(memory);
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - LDA Called Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    m_accumulator = resultValue;

    status_setNegative((m_accumulator & 0b10000000) != 0);
    status_setZero(m_accumulator == 0);

    ostringstream verboseString;
    verboseString << "Loading Accumulator with value 0x" << hex << int(resultValue);
    printVerbose(verboseString.str());
}

void CPU::clearFlag(uint8_t opcode)
{
    switch (opcode)
    {
    case Opcode::CLEAR_CARRY_FLAG:
        status_setCarry(false);
        break;
    case Opcode::CLEAR_DECIMAL_MODE:
        status_setDecimal(false);
        break;
    case Opcode::CLEAR_INTERRUPT_DISABLE:
        status_setInterrupt(false);
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - Clear Flag Called On Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    ostringstream verboseString;
    verboseString << "Status Register Updated: 0b" << bitset<8>(m_statusRegister);
    printVerbose(verboseString.str());
}

void CPU::transferIndexXToStackPointer()
{
    m_stackPointer = m_xIndex;

    ostringstream verboseString;
    verboseString << "Loading Stack Pointer with value 0x" << hex << int(m_stackPointer);
    printVerbose(verboseString.str());
}

void CPU::transferAccumulatorToIndexX()
{
    m_xIndex = m_accumulator;

    status_setNegative((m_xIndex & 0b10000000) != 0);
    status_setZero(m_xIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading Index X with value 0x" << hex << int(m_xIndex);
    printVerbose(verboseString.str());
}

void CPU::transferAccumulatorToIndexY()
{
    m_yIndex = m_accumulator;

    status_setNegative((m_yIndex & 0b10000000) != 0);
    status_setZero(m_yIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading Index Y with value 0x" << hex << int(m_yIndex);
    printVerbose(verboseString.str());
}

void CPU::transferStackPointerToIndexX()
{
    m_xIndex = m_stackPointer;

    status_setNegative((m_xIndex & 0b10000000) != 0);
    status_setZero(m_xIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading Index X with value 0x" << hex << int(m_xIndex);
    printVerbose(verboseString.str());
}

void CPU::transferIndexYToAccumulator()
{
    m_accumulator = m_yIndex;

    status_setNegative((m_accumulator & 0b10000000) != 0);
    status_setZero(m_accumulator == 0);

    ostringstream verboseString;
    verboseString << "Loading Accumulator with value 0x" << hex << int(m_xIndex);
    printVerbose(verboseString.str());
}

void CPU::incrementIndexX()
{
    m_xIndex += 1;

    status_setNegative((m_xIndex & 0b10000000) != 0);
    status_setZero(m_xIndex == 0);

    ostringstream verboseString;
    verboseString << "Index X incremented to value 0x" << hex << int(m_xIndex);
    printVerbose(verboseString.str());
}

void CPU::decrementIndexX()
{
    m_xIndex -= 1;

    status_setNegative((m_xIndex & 0b10000000) != 0);
    status_setZero(m_xIndex == 0);

    ostringstream verboseString;
    verboseString << "Index X decremented to value 0x" << hex << int(m_xIndex);
    printVerbose(verboseString.str());
}

void CPU::decrementIndexY()
{
    m_yIndex -= 1;

    status_setNegative((m_yIndex & 0b10000000) != 0);
    status_setZero(m_yIndex == 0);

    ostringstream verboseString;
    verboseString << "Index Y decremented to value 0x" << hex << int(m_yIndex);
    printVerbose(verboseString.str());
}

void CPU::incrementIndexY()
{
    m_yIndex += 1;

    status_setNegative((m_yIndex & 0b10000000) != 0);
    status_setZero(m_yIndex == 0);

    ostringstream verboseString;
    verboseString << "Index Y incremented to value 0x" << hex << int(m_yIndex);
    printVerbose(verboseString.str());
}

void CPU::incrementZeroPagedAddress(Memory &memory)
{
    uint8_t address = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint16_t zeroPagedAddress = 0x0000 | address;

    uint8_t value = memory.read8(zeroPagedAddress);

    value += 1;

    memory.write8(zeroPagedAddress, value);

    status_setNegative((value & 0b10000000) != 0);
    status_setZero(value == 0);

    ostringstream verboseString;
    verboseString << "Zero Page Address {0x" << hex << int(zeroPagedAddress) << "} incremented to value 0x" << hex << int(value);
    printVerbose(verboseString.str());
}

void CPU::jumpAbsoluteSaveReturn(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    uint8_t programCounterHigh = (uint8_t)(m_programCounter >> 8);
    uint8_t programCounterLow = (uint8_t)m_programCounter;

    uint16_t stackOffset = 0x100;

    memory.write8(stackOffset + m_stackPointer, programCounterHigh);
    m_stackPointer -= 1;
    memory.write8(stackOffset + m_stackPointer, programCounterLow);
    m_stackPointer -= 1;

    m_programCounter = absoluteAddress;

    ostringstream verboseString;
    verboseString << "Jump to {0x" << hex << int(absoluteAddress) << "} with return address {0x"
                  << hex << (int)programCounterHigh << hex << (int)programCounterLow << "}" << endl;
    verboseString << T_DEBUG << "New Stack Pointer value: 0x" << hex << (int)m_stackPointer;
    printVerbose(verboseString.str());
}

void CPU::branchOnStatusRegister(Memory &memory, uint8_t opcode)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    bool isSigned = (immediateValue & 0b10000000) != 0;
    if (isSigned)
    {
        immediateValue = ~immediateValue + 1;
    }

    bool statusValue;
    string opcodeMnemonic;

    switch (opcode)
    {
    case Opcode::BRANCH_ON_CARRY_CLEAR:
        statusValue = !status_getCarry();
        opcodeMnemonic = "BCC";
        break;
    case Opcode::BRANCH_ON_CARRY_SET:
        statusValue = status_getCarry();
        opcodeMnemonic = "BCS";
        break;
    case Opcode::BRANCH_ON_NEGATIVE_CLEAR:
        statusValue = !status_getNegative();
        opcodeMnemonic = "BPL";
        break;
    case Opcode::BRANCH_ON_NEGATIVE_SET:
        statusValue = status_getNegative();
        opcodeMnemonic = "BMI";
        break;
    case Opcode::BRANCH_ON_ZERO_CLEAR:
        statusValue = !status_getZero();
        opcodeMnemonic = "BNE";
        break;
    case Opcode::BRANCH_ON_ZERO_SET:
        statusValue = status_getZero();
        opcodeMnemonic = "BEQ";
        break;
    case Opcode::BRANCH_ON_OVERFLOW_CLEAR:
        statusValue = !status_getOverflow();
        opcodeMnemonic = "BVC";
        break;
    case Opcode::BRANCH_ON_OVERFLOW_SET:
        statusValue = status_getOverflow();
        opcodeMnemonic = "BVS";
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - Branch Called On Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    ostringstream verboseString;

    if (statusValue)
    {
        if (isSigned)
        {
            m_programCounter -= immediateValue;
            verboseString << opcodeMnemonic << " - PC decremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
        else
        {
            m_programCounter += immediateValue;
            verboseString << opcodeMnemonic << " - PC incremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
    }
    else
    {
        verboseString << opcodeMnemonic << " - No Action Taken";
    }

    printVerbose(verboseString.str());
}

void CPU::returnFromSubroutine(Memory &memory)
{
    uint16_t stackOffset = 0x100;
    stackOffset += m_stackPointer + 1;

    uint16_t returnAddress = memory.read16(stackOffset);

    m_stackPointer += 2;

    m_programCounter = returnAddress;

    ostringstream verboseString;
    verboseString << "Returned from subroutine to address {0x" << hex << int(m_programCounter) << "}";
    printVerbose(verboseString.str());
}

void CPU::absoluteBitwiseTest(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    uint8_t memoryValue = memory.read8(absoluteAddress);
    uint8_t resultValue = memoryValue & m_accumulator;

    // Accumulator only affects zero flag
    // Other to status flags are based on the value read from memory
    status_setZero(resultValue == 0);
    status_setNegative((memoryValue & 0b10000000) != 0);
    status_setOverflow((memoryValue & 0b01000000) != 0);

    ostringstream verboseString;
    verboseString << "Bitwise Test with value 0x" << hex << int(resultValue) << " from absolute address {0x" << hex << int(absoluteAddress) << "} set status register to 0b" << bitset<8>(m_statusRegister);
    printVerbose(verboseString.str());
}

void CPU::orMemoryWithAccumulatorAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    uint8_t memoryValue = memory.read8(absoluteAddress);
    uint8_t resultValue = memoryValue | m_accumulator;

    m_accumulator = resultValue;

    status_setZero(resultValue == 0);
    status_setNegative((resultValue & 0b10000000) != 0);

    ostringstream verboseString;
    verboseString << "OR with value 0x" << hex << int(memoryValue) << " at address {0x" << hex << int(absoluteAddress) << "} and accumulator value 0x" << hex << int(m_accumulator) << " set status register to 0b" << bitset<8>(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::andAccumulatorWithImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint8_t resultValue = immediateValue | m_accumulator;

    m_accumulator = resultValue;

    status_setZero(resultValue == 0);
    status_setNegative((resultValue & 0b10000000) != 0);

    ostringstream verboseString;
    verboseString << "AND with immediate value 0x" << hex << int(immediateValue) << " and accumulator value 0x" << hex << int(m_accumulator) << " set status register to 0b" << bitset<8>(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::pushAccumulatorToStack(Memory &memory)
{
    memory.write8(m_stackPointer + 0x100, m_accumulator);
    m_stackPointer -= 1;

    ostringstream verboseString;
    verboseString << "Pushed accumulator value 0x" << hex << int(m_accumulator) << " to stack" << endl;
    verboseString << T_DEBUG << "New Stack Pointer value: 0x" << hex << (int)m_stackPointer;
    printVerbose(verboseString.str());
}

void CPU::pushStatusToStack(Memory &memory)
{
    memory.write8(m_stackPointer + 0x100, m_statusRegister);
    m_stackPointer -= 1;

    ostringstream verboseString;
    verboseString << "Pushed status value 0x" << hex << int(m_accumulator) << " to stack" << endl;
    verboseString << T_DEBUG << "New Stack Pointer value: 0x" << hex << (int)m_stackPointer;
    printVerbose(verboseString.str());
}

void CPU::pullAccumulatorFromStack(Memory &memory)
{
    m_stackPointer += 1;
    uint8_t pulledValue = memory.read8(m_stackPointer + 0x100);

    m_accumulator = pulledValue;

    status_setZero(m_accumulator == 0);
    status_setNegative((m_accumulator & 0b10000000) != 0);

    ostringstream verboseString;
    verboseString << "Pulled accumulator value 0x" << hex << int(m_accumulator) << " from stack" << endl;
    verboseString << T_DEBUG << "New Stack Pointer value: 0x" << hex << (int)m_stackPointer;
    printVerbose(verboseString.str());
}

void CPU::pullStatusFromStack(Memory &memory)
{
    m_stackPointer += 1;
    uint8_t pulledValue = memory.read8(m_stackPointer + 0x100);

    m_statusRegister = pulledValue;

    ostringstream verboseString;
    verboseString << "Pulled accumulator value 0x" << hex << int(m_accumulator) << " from stack" << endl;
    verboseString << T_DEBUG << "New Stack Pointer value: 0x" << hex << (int)m_stackPointer;
    printVerbose(verboseString.str());
}

void CPU::compareWithImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint8_t result = m_accumulator - immediateValue;
    setCompareStatus(m_accumulator, immediateValue, result);

    ostringstream verboseString;
    verboseString << "Compare between accumulator 0x" << hex << int(m_accumulator) << " and immediate value 0x" << hex << int(immediateValue) << " set status register to 0x" << hex << int(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::compareIndexX(Memory &memory, uint8_t opcode)
{
    uint8_t operand;

    switch (opcode)
    {
    case Opcode::COMPARE_IMMEDIATE_AND_INDEX_X:
        operand = getImmediate(memory);
        break;
    case Opcode::COMPARE_ABSOLUTE_AND_INDEX_X:
        operand = getAbsolute(memory);
        break;
    case Opcode::COMPARE_ZERO_PAGE_AND_INDEX_X:
        operand = getZeroPage(memory);
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - CPX Called On Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    uint8_t result = m_xIndex - operand;
    setCompareStatus(m_xIndex, operand, result);

    ostringstream verboseString;
    verboseString << "Compare between index x 0x" << hex << int(m_xIndex) << " and value 0x" << hex << int(operand) << " set status register to 0x" << hex << int(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::compareIndexY(Memory &memory, uint8_t opcode)
{
    uint8_t operand;

    switch (opcode)
    {
    case Opcode::COMPARE_IMMEDIATE_AND_INDEX_Y:
        operand = getImmediate(memory);
        break;
    case Opcode::COMPARE_ABSOLUTE_AND_INDEX_Y:
        operand = getAbsolute(memory);
        break;
    case Opcode::COMPARE_ZERO_PAGE_AND_INDEX_Y:
        operand = getZeroPage(memory);
        break;
    default:
        cout << T_ERROR << "Emulator Opcode Error - CPY Called On Invalid Opcode 0x" << hex << int(opcode) << endl;
        exit(0);
    }

    uint8_t result = m_yIndex - operand;
    setCompareStatus(m_yIndex, operand, result);

    ostringstream verboseString;
    verboseString << "Compare between index x 0x" << hex << int(m_yIndex) << " and value 0x" << hex << int(operand) << " set status register to 0x" << hex << int(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::subractImmediateWithBorrow(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint8_t invertedCarryValue = (uint8_t) !(status_getCarry());

    uint8_t accumulatorTemp = m_accumulator;
    uint8_t subractValue = immediateValue + invertedCarryValue;

    m_accumulator = m_accumulator - subractValue;

    status_setZero(m_accumulator != 0);
    status_setNegative((m_accumulator & 0b1000000) != 0);
    status_setCarry(m_accumulator >= accumulatorTemp and subractValue > 0);

    bool accumulatorTempPositive = (accumulatorTemp & 0b1000000) == 0;
    bool subtractValuePositive = (subractValue & 0b1000000) == 0;
    bool resultPositive = (m_accumulator & 0b1000000) == 0;

    if (accumulatorTempPositive && subtractValuePositive)
    {
        status_setOverflow(!resultPositive);
    }
    else if (!accumulatorTempPositive && !subtractValuePositive)
    {
        status_setOverflow(resultPositive);
    }
    else
    {
        status_setOverflow(false);
    }

    ostringstream verboseString;
    verboseString << "Accumulator subtracted to 0x" << hex << int(m_accumulator) << " and set status register to 0x" << hex << int(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::addImmediateWithBorrow(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    uint8_t accumulatorTemp = m_accumulator;
    uint8_t addValue = immediateValue + status_getCarry();

    m_accumulator = m_accumulator + addValue;

    status_setZero(m_accumulator != 0);
    status_setNegative((m_accumulator & 0b1000000) != 0);
    status_setCarry(m_accumulator <= accumulatorTemp && addValue > 0);

    bool accumulatorTempPositive = (accumulatorTemp & 0b1000000) == 0;
    bool addValuePositive = (addValue & 0b1000000) == 0;
    bool resultPositive = (m_accumulator & 0b1000000) == 0;

    if (accumulatorTempPositive && addValuePositive)
    {
        status_setOverflow(!resultPositive);
    }
    else if (!accumulatorTempPositive && !addValuePositive)
    {
        status_setOverflow(resultPositive);
    }
    else
    {
        status_setOverflow(false);
    }

    ostringstream verboseString;
    verboseString << "Accumulator incremented to 0x" << hex << int(m_accumulator) << " and set status register to 0x" << hex << int(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::shiftRightAccumulator()
{
    bool carryFlag = (m_accumulator & 0b00000001) != 0;

    m_accumulator = m_accumulator >> 1;

    status_setNegative(false);
    status_setZero(m_accumulator == 0);
    status_setCarry(carryFlag);

    ostringstream verboseString;
    verboseString << "Accumulator shifted right to 0x" << hex << int(m_accumulator) << " and set status register to 0x" << hex << int(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::printVerbose(string verboseString)
{
    if (PRINT_VERBOSE_OPCODE_DEBUG)
    {
        cout << T_DEBUG << verboseString << endl;
    }

    if (PRINT_STATUS_DEBUG)
    {
        cout << T_DEBUG << "|Status Register: 0b" << bitset<8>(m_statusRegister) << "|" << endl;
        ;
    }
}

void CPU::status_setNegative(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b10000000;
    }
    else
    {
        m_statusRegister &= 0b01111111;
    }
}

void CPU::status_setOverflow(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b01000000;
    }
    else
    {
        m_statusRegister &= 0b10111111;
    }
}
void CPU::status_setBreak(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b00010000;
    }
    else
    {
        m_statusRegister &= 0b11101111;
    }
}
void CPU::status_setDecimal(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b00001000;
    }
    else
    {
        m_statusRegister &= 0b11110111;
    }
}
void CPU::status_setInterrupt(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b00000100;
    }
    else
    {
        m_statusRegister &= 0b11111011;
    }
}
void CPU::status_setZero(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b00000010;
    }
    else
    {
        m_statusRegister &= 0b11111101;
    }
}
void CPU::status_setCarry(bool value)
{
    if (value)
    {
        m_statusRegister |= 0b00000001;
    }
    else
    {
        m_statusRegister &= 0b11111110;
    }
}

bool CPU::status_getNegative()
{
    return (m_statusRegister & 0b10000000) != 0;
}
bool CPU::status_getOverflow()
{
    return (m_statusRegister & 0b01000000) != 0;
}
bool CPU::status_getBreak()
{
    return (m_statusRegister & 0b00010000) != 0;
}
bool CPU::status_getDecimal()
{
    return (m_statusRegister & 0b00001000) != 0;
}
bool CPU::status_getInterrupt()
{
    return (m_statusRegister & 0b00000100) != 0;
}
bool CPU::status_getZero()
{
    return (m_statusRegister & 0b00000010) != 0;
}
bool CPU::status_getCarry()
{
    return (m_statusRegister & 0b00000001) != 0;
}

uint8_t CPU::getAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;
    return memory.read8(absoluteAddress);
}

uint8_t CPU::getAbsoluteYIndexed(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;
    return memory.read8(absoluteAddress + m_yIndex);
}

uint8_t CPU::getAbsoluteXIndexed(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;
    return memory.read8(absoluteAddress + m_xIndex);
}

uint8_t CPU::getImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;
    return immediateValue;
}

uint8_t CPU::getZeroPage(Memory &memory)
{
    uint8_t zeroPageOffset = getImmediate(memory);

    uint16_t zeroPageAddress = 0x0000 | zeroPageOffset;

    return memory.read8(zeroPageAddress);
}

uint8_t CPU::getZeroPageXIndexed(Memory &memory)
{
    uint8_t zeroPageOffset = getImmediate(memory);

    zeroPageOffset += m_xIndex;

    uint16_t zeroPageAddress = 0x0000 | zeroPageOffset;

    return memory.read8(zeroPageAddress);
}

uint8_t CPU::getZeroPageYIndexed(Memory &memory)
{
    uint8_t zeroPageOffset = getImmediate(memory);

    zeroPageOffset += m_yIndex;

    uint16_t zeroPageAddress = 0x0000 | zeroPageOffset;

    return memory.read8(zeroPageAddress);
}

void CPU::setCompareStatus(uint8_t registerValue, uint8_t operand, uint8_t result)
{
    if (result == 0)
    {
        status_setZero(true);
        status_setCarry(true);
        status_setNegative(false);
    }
    else
    {
        status_setCarry(registerValue > operand);
        status_setZero(false);
        status_setNegative((result & 0b1000000) != 0);
    }
}
