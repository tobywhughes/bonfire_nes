#include <iostream>
#include "Debug.h"
#include "../enums/opcode.h"
#include "../terminal.h"

using namespace std;

void Debug::opcodeDebugOutput(uint8_t opcode, uint16_t programCounter, bool printDebug)
{
    string opcodeDebugString;

    switch (opcode)
    {
    case Opcode::SET_INTERRUPT_DISABLE:
        opcodeDebugString = "<SIE> Set Interrupt Disable";
        break;
    case Opcode::JUMP_ABSOLUTE:
        opcodeDebugString = "<JMP abs> - Jump Absolute";
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE:
        opcodeDebugString = "<STA abs> - Store Accumulator At Absolute Address";
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ABSOLUTE_X_INDEXED:
        opcodeDebugString = "<STA abs,X> - Store Accumulator At Absolute Address X-Indexed";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
        opcodeDebugString = "<LDA imm> - Load Accumulator With Immediate Value";
        break;
    case Opcode::CLEAR_DECIMAL_MODE:
        opcodeDebugString = "<CLD> - Clear Decimal Mode";
        break;
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
        opcodeDebugString = "<LDX imm> - Load Index X With Immediate Value";
        break;
    case Opcode::LOAD_INDEX_Y_WITH_IMMEDIATE:
        opcodeDebugString = "<LDY imm> - Load Index Y With Immediate Value";
        break;
    case Opcode::TRANSFER_INDEX_X_TO_STACK_POINTER:
        opcodeDebugString = "<TXS> - Transfer Index X To Stack Pointer";
        break;
    case Opcode::TRANSFER_ACCUMULATOR_TO_INDEX_X:
        opcodeDebugString = "<TAX> - Transfer Accumulator To Index X";
        break;
    case Opcode::TRANSFER_STACK_POINTER_TO_INDEX_X:
        opcodeDebugString = "<TSX> - Transfer Stack Pointer To Index X";
        break;
    case Opcode::TRANSFER_INDEX_Y_TO_ACCUMULATOR:
        opcodeDebugString = "<TYA> - Transfer Index Y To Accumulator";
        break;
    case Opcode::INCREMENT_INDEX_X:
        opcodeDebugString = "<INX> - Increment Index X";
        break;
    case Opcode::DECREMENT_INDEX_X:
        opcodeDebugString = "<DEX> - Decrement Index X";
        break;
    case Opcode::DECREMENT_INDEX_Y:
        opcodeDebugString = "<DEY> - Decrement Index Y";
        break;
    case Opcode::INCREMENT_INDEX_Y:
        opcodeDebugString = "<INY> - Increment Index Y";
        break;
    case Opcode::STORE_INDEX_X_AT_ABSOLUTE:
        opcodeDebugString = "<STX abs> - Store Index X At Absolute Address";
        break;
    case Opcode::JUMP_ABSOLUTE_SAVE_RETURN:
        opcodeDebugString = "<JSR abs> - Jump Absolute Save Return Address";
        break;
    case Opcode::STORE_INDEX_Y_AT_ZERO_PAGE:
        opcodeDebugString = "<STY d> - Store Index Y At Zero Page Address";
        break;
    case Opcode::STORE_INDEX_X_AT_ZERO_PAGE:
        opcodeDebugString = "<STX d> - Store Index X At Zero Page Address";
        break;
    case Opcode::STORE_ACCUMULATOR_AT_INDIRECT_Y_INDEXED:
        opcodeDebugString = "<STA (d),y> - Store Accumulator At indirect y-indexed";
        break;
    case Opcode::STORE_ACCUMULATOR_AT_ZEROPAGE_X_INDEXED:
        opcodeDebugString = "<STA d,x> - Store Accumulator At zero page x-indexed";
        break;
    case Opcode::BRANCH_ON_ZERO_CLEAR:
        opcodeDebugString = "<BNE rel> - Branch On Zero Clear";
        break;
    case Opcode::BRANCH_ON_NEGATIVE_SET:
        opcodeDebugString = "<BMI> - Branch On Negative Set";
        break;
    case Opcode::BRANCH_ON_NEGATIVE_CLEAR:
        opcodeDebugString = "<BPL> - Branch On Negative Clear";
        break;
    case Opcode::INCREMENT_ZERO_PAGED_ADDRESS:
        opcodeDebugString = "<INC d> - Increment Zero Paged Address";
        break;
    case Opcode::RETURN_FROM_SUBROUTINE:
        opcodeDebugString = "<RTS> - Return From Subroutine";
        break;
    case Opcode::ABSOLUTE_BITWISE_TEST:
        opcodeDebugString = "<BIT abs> - Absolute Bitwise Test";
        break;
    case Opcode::UNKNOWN_OPCODE:
    default:
        opcodeDebugString = "Unknown Opcode";
        cout << T_WARNING << "[0x" << hex << (int)programCounter << "] 0x" << hex << (int)opcode << " - " << opcodeDebugString << endl;
        return;
    }

    if (printDebug)
    {
        cout << T_INFO
             << "[0x" << hex << (int)programCounter << "] 0x" << hex << (int)opcode << " - " << opcodeDebugString << endl;
    }
}