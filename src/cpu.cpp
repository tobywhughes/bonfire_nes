#include <iostream>
#include "cpu.h"
#include "terminal.h"
#include <sstream>
#include <bitset>

using namespace std;

const bool PRINT_OPCODE_DEBUG = true;
const bool PRINT_VERBOSE_OPCODE_DEBUG = PRINT_OPCODE_DEBUG && true;

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

void CPU::execute(Memory &memory)
{
    uint16_t opcode = memory.read8(m_programCounter);
    opcodeDebugOutput(opcode);

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
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
        loadAccumulatorWithImmediate(memory);
        break;
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
        loadXIndexWithImmediate(memory);
        break;
    case Opcode::CLEAR_DECIMAL_MODE:
        clearDecimalMode();
        break;
    case Opcode::TRANSFER_INDEX_X_TO_STACK_POINTER:
        transferIndexXToStackPointer();
        break;
    case Opcode::INCREMENT_INDEX_X:
        incrementIndexX();
        break;
    case Opcode::STORE_INDEX_X_AT_ABSOLUTE:
        storeIndexXAtAbsolute(memory);
        break;
    case Opcode::JUMP_ABSOLUTE_SAVE_RETURN:
        jumpAbsoluteSaveReturn(memory);
        break;
    case Opcode::UNKNOWN_OPCODE:
    default:
        cout << T_ERROR << "Unimplemented Opcode: 0x" << hex << (int)opcode << endl;
        cout << T_ERROR << "Exiting Program" << endl;
        exit(0);
        break;
    }
}

void CPU::setInterruptDisable()
{
    m_statusRegister = m_statusRegister | 0b00000100;

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

    ostringstream verboseString;
    verboseString << "Loading Accumulator with value 0x" << hex << int(immediateValue);
    printVerbose(verboseString.str());
}

void CPU::loadXIndexWithImmediate(Memory &memory)
{
    uint8_t immediateValue = memory.read8(m_programCounter);
    m_programCounter += 1;

    m_xIndex = immediateValue;

    ostringstream verboseString;
    verboseString << "Loading Accumulator with value 0x" << hex << int(immediateValue);
    printVerbose(verboseString.str());
}

void CPU::clearDecimalMode()
{
    m_statusRegister = m_statusRegister & 0b11111101;

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

void CPU::incrementIndexX()
{
    m_xIndex += 1;

    ostringstream verboseString;
    verboseString << "Index X  incremented with value 0x" << hex << int(m_xIndex);
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
    memory.write8(stackOffset + m_stackPointer, programCounterHigh);
    m_stackPointer -= 1;

    m_programCounter = absoluteAddress;

    ostringstream verboseString;
    verboseString << "Jump to {0x" << hex << int(absoluteAddress) << "} with return address {0x"
                  << hex << (int)programCounterHigh << hex << (int)programCounterLow << "}" << endl;
    verboseString << T_DEBUG << "New Stack Pointer value: 0x" << hex << (int)m_stackPointer;
    printVerbose(verboseString.str());
}

void CPU::printVerbose(string verboseString)
{
    if (PRINT_VERBOSE_OPCODE_DEBUG)
    {
        cout << T_DEBUG << verboseString << endl;
    }
}

void CPU::opcodeDebugOutput(uint8_t opcode)
{
    string opcodeDebugString;

    switch (opcode)
    {
    case Opcode::SET_INTERRUPT_DISABLE:
        opcodeDebugString = "<SIE> Set Interrupt Disable";
        break;
    case Opcode::JUMP_ABSOLUTE:
        opcodeDebugString = "<JMP abs> Jump Absolute";
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE:
        opcodeDebugString = "<STA abs> Store Accumulator At Absolute Address";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
        opcodeDebugString = "<LDA imm> Load Accumulator With Immediate Value";
        break;
    case Opcode::CLEAR_DECIMAL_MODE:
        opcodeDebugString = "<CLD> Clear Decimal Mode";
        break;
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
        opcodeDebugString = "<LDC imm> - Load Index X With Immediate Value";
        break;
    case Opcode::TRANSFER_INDEX_X_TO_STACK_POINTER:
        opcodeDebugString = "<TXS> - Transfer Index X To Stack Pointer";
        break;
    case Opcode::INCREMENT_INDEX_X:
        opcodeDebugString = "<INX> - Increment Index X";
        break;
    case Opcode::STORE_INDEX_X_AT_ABSOLUTE:
        opcodeDebugString = "<STX abs> Store Index X At Absolute Address";
        break;
    case Opcode::JUMP_ABSOLUTE_SAVE_RETURN:
        opcodeDebugString = "<JSR abs> Jump Absolute Save Return Address";
        break;
    case Opcode::UNKNOWN_OPCODE:
    default:
        opcodeDebugString = "Unknown Opcode";
    }

    if (PRINT_OPCODE_DEBUG)
    {
        cout << T_INFO
             << "[0x" << hex << (int)m_programCounter << "] 0x" << hex << (int)opcode << " - " << opcodeDebugString << endl;
    }
}