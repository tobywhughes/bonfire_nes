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
    case Opcode::CLEAR_INTERRUPT_DISABLE:
        opcodeDebugString = "<CLI> Clear Interrupt Disable";
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

    case Opcode::CLEAR_DECIMAL_MODE:
        opcodeDebugString = "<CLD> - Clear Decimal Mode";
        break;
    case Opcode::TRANSFER_INDEX_X_TO_STACK_POINTER:
        opcodeDebugString = "<TXS> - Transfer Index X To Stack Pointer";
        break;
    case Opcode::TRANSFER_ACCUMULATOR_TO_INDEX_X:
        opcodeDebugString = "<TAX> - Transfer Accumulator To Index X";
        break;
    case Opcode::TRANSFER_ACCUMULATOR_TO_INDEX_Y:
        opcodeDebugString = "<TAY> - Transfer Accumulator To Index Y";
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
    case Opcode::STORE_ACCUMULATOR_AT_ZERO_PAGE:
        opcodeDebugString = "<STA d> - Store Accumulator At Zero Page Address";
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
        opcodeDebugString = "<BNE> - Branch On Zero Clear";
        break;
    case Opcode::BRANCH_ON_ZERO_SET:
        opcodeDebugString = "<BEQ> - Branch On Zero Set";
        break;
    case Opcode::BRANCH_ON_NEGATIVE_SET:
        opcodeDebugString = "<BMI> - Branch On Negative Set";
        break;
    case Opcode::BRANCH_ON_CARRY_SET:
        opcodeDebugString = "<BCS> - Branch On Carry Set";
        break;
    case Opcode::BRANCH_ON_NEGATIVE_CLEAR:
        opcodeDebugString = "<BPL> - Branch On Negative Clear";
        break;
    case Opcode::BRANCH_ON_CARRY_CLEAR:
        opcodeDebugString = "<BCC> - Branch On Carry Clear";
        break;
    case Opcode::BRANCH_ON_OVERFLOW_CLEAR:
        opcodeDebugString = "<BVC> - Branch On Overflow Clear";
        break;
    case Opcode::BRANCH_ON_OVERFLOW_SET:
        opcodeDebugString = "<BVS> - Branch On Overflow Set";
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
    case Opcode::OR_MEMORY_WITH_ACCUMULATOR_ABSOLUTE:
        opcodeDebugString = "<ORA abs> - Or absolute memory with accumulator";
        break;
    case Opcode::PUSH_ACCUMULATOR_TO_STACK:
        opcodeDebugString = "<PHA> - Push Accumulator To Stack";
        break;
    case Opcode::PULL_ACCUMULATOR_FROM_STACK:
        opcodeDebugString = "<PLA> - Pull Accumulator From Stack";
        break;
    case Opcode::PULL_STATUS_FROM_STACK:
        opcodeDebugString = "<PLP> - Pull Status From Stack";
        break;
    case Opcode::PUSH_STATUS_TO_STACK:
        opcodeDebugString = "<PHP> - Push Status To Stack";
        break;
    case Opcode::COMPARE_WITH_IMMEDIATE:
        opcodeDebugString = "<CMP imm> - Compare With Immediate";
        break;
    case Opcode::SUBRACT_IMMEDIATE_WITH_BORROW:
        opcodeDebugString = "<SBC imm> - Subract Immediate With Borrow";
        break;
    case Opcode::ADD_IMMEDIATE_WITH_BORROW:
        opcodeDebugString = "<ABC imm> - Add Immediate With Borrow";
        break;
    case Opcode::SHIFT_RIGHT_ACCUMULATOR:
        opcodeDebugString = "<LSR A> - Shift Right Accumulator";
        break;
    case Opcode::CLEAR_CARRY_FLAG:
        opcodeDebugString = "<CLC> - Clear Carry Flag";
        break;
    case Opcode::AND_ACCUMULATOR_WITH_IMMEDIATE:
        opcodeDebugString = "<AND imm> - AND Accumulator With Immediate";
        break;
    case Opcode::LOAD_INDEX_X_WITH_ABSOLUTE:
        opcodeDebugString = "<LDX abs> - Load Index X With Absolute";
        break;
    case Opcode::LOAD_INDEX_X_WITH_IMMEDIATE:
        opcodeDebugString = "<LDX imm> - Load Index X With Immediate Value";
        break;
    case Opcode::LOAD_INDEX_X_WITH_ZERO_PAGE:
        opcodeDebugString = "<LDX zpg> - Load Index X With Zero Page";
        break;
    case Opcode::LOAD_INDEX_X_ZERO_PAGE_Y_INDEXED:
        opcodeDebugString = "<LDX zpg,y> - Load Index X With Zero Page Y Indexed";
        break;
    case Opcode::LOAD_INDEX_X_WITH_ABSOLUTE_Y_INDEXED:
        opcodeDebugString = "<LDX abs,y> - Load Index X With Absolute Y Indexed";
        break;
    case Opcode::LOAD_INDEX_Y_WITH_ABSOLUTE:
        opcodeDebugString = "<LDY abs> - Load Index Y With Absolute";
        break;
    case Opcode::LOAD_INDEX_Y_WITH_IMMEDIATE:
        opcodeDebugString = "<LDY imm> - Load Index Y With Immediate Value";
        break;
    case Opcode::LOAD_INDEX_Y_WITH_ZERO_PAGE:
        opcodeDebugString = "<LDY zpg> - Load Index Y With Zero Page";
        break;
    case Opcode::LOAD_INDEX_Y_ZERO_PAGE_X_INDEXED:
        opcodeDebugString = "<LDY zpg,x> - Load Index Y With Zero Page X Indexed";
        break;
    case Opcode::LOAD_INDEX_Y_WITH_ABSOLUTE_X_INDEXED:
        opcodeDebugString = "<LDY abs,x> - Load Index Y With Absolute X Indexed";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE:
        opcodeDebugString = "<LDY abs> - Load Accumulator With Absolute";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_IMMEDIATE:
        opcodeDebugString = "<LDA imm> - Load Accumulator With Immediate Value";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ZERO_PAGE:
        opcodeDebugString = "<LDA zpg> - Load Accumulator With Zero Page";
        break;
    case Opcode::LOAD_ACCUMULATOR_ZERO_PAGE_X_INDEXED:
        opcodeDebugString = "<LDA zpg,x> - Load Accumulator With Zero Page X Indexed";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_ABSOLUTE_X_INDEXED:
        opcodeDebugString = "<LDA abs,x> - Load Accumulator With Absolute X Indexed";
        break;
    case Opcode::LOAD_ACCUMULATOR_WITH_INDIRECT_Y_INDEXED:
        opcodeDebugString = "<LDA abs,y> - Load Accumulator With Absolute Y Indexed";
        break;
    case Opcode::COMPARE_IMMEDIATE_AND_INDEX_X:
        opcodeDebugString = "<CPX imm> - Compare Immediate With Index X";
        break;
    case Opcode::COMPARE_ABSOLUTE_AND_INDEX_X:
        opcodeDebugString = "<CPX abs> - Compare Absolute With Index X";
        break;
    case Opcode::COMPARE_ZERO_PAGE_AND_INDEX_X:
        opcodeDebugString = "<CPX zpg> - Compare Zero Page With Index X";
        break;
    case Opcode::COMPARE_IMMEDIATE_AND_INDEX_Y:
        opcodeDebugString = "<CPY imm> - Compare Immediate With Index X";
        break;
    case Opcode::COMPARE_ABSOLUTE_AND_INDEX_Y:
        opcodeDebugString = "<CPY abs> - Compare Absolute With Index X";
        break;
    case Opcode::COMPARE_ZERO_PAGE_AND_INDEX_Y:
        opcodeDebugString = "<CPY zpg> - Compare Zero Page With Index X";
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