#include <iostream>
#include "cpu.h"

using namespace std;

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
    case Opcode::UNKNOWN_OPCODE:
    default:
        cout << "Unkown Opcode: 0x" << hex << (int)opcode << endl;
        cout << "Exiting Program" << endl;
        exit(0);
        break;
    }
}

void CPU::setInterruptDisable()
{
    m_statusRegister = m_statusRegister | 0b00000100;
}

void CPU::opcodeDebugOutput(uint8_t opcode)
{
    switch (opcode)
    {
    case Opcode::SET_INTERRUPT_DISABLE:
        cout << "[0x" << hex << (int)m_programCounter << "] 0x" << hex << (int)opcode << " - Set Interrupt Disable" << endl;
        break;
    case Opcode::UNKNOWN_OPCODE:
    default:
        cout << "[0x" << hex << (int)m_programCounter << "] 0x" << hex << (int)opcode << " - Unknown Opcode" << endl;
    }
}