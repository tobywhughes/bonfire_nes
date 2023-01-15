#include <iostream>
#include "cpu.h"
#include "terminal.h"
#include <sstream>
#include <bitset>
#include "Utils/Debug.h"

using namespace std;

const bool PRINT_OPCODE_DEBUG = false;
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
    case Opcode::JUMP_ABSOLUTE:
        jumpAbsolute(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE:
        storeAccumulatorAtAbsolute(memory);
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE_X_INDEXED:
        storeAccumulatorAtAbsoluteXIndexed(memory);
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
        loadAccumulatorWithImmediate(memory);
        break;
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
        loadXIndexWithImmediate(memory);
        break;
    case Opcode::LOAD_INDEX_Y_WITH_IMMEDIATE:
        loadIndexYWithImmediate(memory);
        break;
    case Opcode::CLEAR_DECIMAL_MODE:
        clearDecimalMode();
        break;
    case Opcode::TRANSFER_INDEX_X_TO_STACK_POINTER:
        transferIndexXToStackPointer();
        break;
    case Opcode::TRANSFER_ACCUMULATOR_TO_INDEX_X:
        transferAccumulatorToIndexX();
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
        branchOnZeroClear(memory);
        break;
    case Opcode::BRANCH_ON_NEGATIVE_SET:
        branchOnNegativeSet(memory);
        break;
    case Opcode::BRANCH_ON_NEGATIVE_CLEAR:
        branchOnNegativeClear(memory);
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

void CPU::storeIndexXAtAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    memory.write8(absoluteAddress, m_xIndex);

    ostringstream verboseString;
    verboseString << "Storing Index X value 0x" << hex << int(m_xIndex) << " at address {0x" << hex << int(absoluteAddress) << "}";
    printVerbose(verboseString.str());
}

void CPU::loadAccumulatorWithImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    m_accumulator = immediateValue;

    status_setNegative((m_accumulator & 0b10000000) != 0);
    status_setZero(m_accumulator == 0);

    ostringstream verboseString;
    verboseString << "Loading Accumulator with value 0x" << hex << int(immediateValue);
    printVerbose(verboseString.str());
}

void CPU::loadXIndexWithImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    m_xIndex = immediateValue;

    status_setNegative((m_xIndex & 0b10000000) != 0);
    status_setZero(m_xIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading X Index with value 0x" << hex << int(immediateValue);
    printVerbose(verboseString.str());
}

void CPU::loadIndexYWithImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    m_yIndex = immediateValue;

    status_setNegative((m_yIndex & 0b10000000) != 0);
    status_setZero(m_yIndex == 0);

    ostringstream verboseString;
    verboseString << "Loading Y Index with value 0x" << hex << int(immediateValue);
    printVerbose(verboseString.str());
}

void CPU::clearDecimalMode()
{
    status_setDecimal(false);

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
    verboseString << "Loading Accumulator with value 0x" << hex << int(m_xIndex);
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

void CPU::branchOnZeroClear(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    bool isSigned = (immediateValue & 0b10000000) != 0;
    if (isSigned)
    {
        immediateValue = ~immediateValue + 1;
    }

    bool zeroStatus = status_getZero();

    ostringstream verboseString;

    if (!zeroStatus)
    {
        if (isSigned)
        {
            m_programCounter -= immediateValue;
            verboseString << "BNE - PC decremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
        else
        {
            m_programCounter += immediateValue;
            verboseString << "BNE - PC incremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
    }
    else
    {
        verboseString << "BNE - No Action Taken";
    }

    printVerbose(verboseString.str());
}

void CPU::branchOnNegativeSet(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    bool isSigned = (immediateValue & 0b10000000) != 0;
    if (isSigned)
    {
        immediateValue = ~immediateValue + 1;
    }

    bool negativeStatus = status_getNegative();

    ostringstream verboseString;

    if (negativeStatus)
    {
        if (isSigned)
        {
            m_programCounter -= immediateValue;
            verboseString << "BMI - PC decremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
        else
        {
            m_programCounter += immediateValue;
            verboseString << "BMI - PC incremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
    }
    else
    {
        verboseString << "BMI - No Action Taken";
    }

    printVerbose(verboseString.str());
}

void CPU::branchOnNegativeClear(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    bool isSigned = (immediateValue & 0b10000000) != 0;
    if (isSigned)
    {
        immediateValue = ~immediateValue + 1;
    }

    bool negativeStatus = status_getNegative();

    ostringstream verboseString;

    if (!negativeStatus)
    {
        if (isSigned)
        {
            m_programCounter -= immediateValue;
            verboseString << "BPL - PC decremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
        else
        {
            m_programCounter += immediateValue;
            verboseString << "BPL - PC incremented by " << unsigned(immediateValue) << " to {0x" << hex << int(m_programCounter) << "}";
        }
    }
    else
    {
        verboseString << "BPL - No Action Taken";
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
    verboseString << "Returned from subroutine to address {0x" << hex << int(m_programCounter) << "}" << endl;
    printVerbose(verboseString.str());
}

void CPU::absoluteBitwiseTest(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    uint8_t memoryValue = memory.read8(absoluteAddress);
    uint8_t resultValue = memoryValue & m_accumulator;

    status_setZero(resultValue == 0);
    status_setNegative((resultValue & 0b10000000) != 0);
    status_setOverflow((resultValue & 0b01000000) != 0);

    ostringstream verboseString;
    verboseString << "Bitwise Test with value 0x" << hex << int(resultValue) << " set status register to 0b" << bitset<8>(m_statusRegister) << endl;
    printVerbose(verboseString.str());
}

void CPU::orMemoryWithAccumulatorAbsolute(Memory &memory)
{
    uint16_t absoluteAddress = memory.read16(m_programCounter);
    m_programCounter += 2;

    uint8_t memoryValue = memory.read8(absoluteAddress);
    uint8_t resultValue = memoryValue | m_accumulator;

    status_setZero(resultValue == 0);
    status_setNegative((resultValue & 0b10000000) != 0);

    ostringstream verboseString;
    verboseString << "OR with value 0x" << hex << int(memoryValue) << " at address {0x" << hex << int(absoluteAddress) << "} and accumulator value 0x" << hex << int(m_accumulator) << " set status register to 0b" << bitset<8>(m_statusRegister) << endl;
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