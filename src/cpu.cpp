#include <iostream>
#include "cpu.h"
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
    cout << "PC Initialized To: 0x" << hex << (int)m_programCounter << endl;
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
    case Opcode::UNKNOWN_OPCODE:
    default:
        cout << "Unimplemented Opcode: 0x" << hex << (int)opcode << endl;
        cout << "Exiting Program" << endl;
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

void CPU::printVerbose(string verboseString)
{
    if (PRINT_VERBOSE_OPCODE_DEBUG)
    {
        cout << ":: " << verboseString << endl;
    }
}

void CPU::opcodeDebugOutput(uint8_t opcode)
{
    string opcodeDebugString;

    switch (opcode)
    {
    case Opcode::SET_INTERRUPT_DISABLE:
        opcodeDebugString = "Set Interrupt Disable";
        break;
    case Opcode::JUMP_ABSOLUTE:
        opcodeDebugString = "Jump Absolute";
        break;
    case Opcode::UNKNOWN_OPCODE:
    default:
        opcodeDebugString = "Unknown Opcode";
    }

    if (PRINT_OPCODE_DEBUG)
    {
        cout << "[0x" << hex << (int)m_programCounter << "] 0x" << hex << (int)opcode << " - " << opcodeDebugString << endl;
    }
}