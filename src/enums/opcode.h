#ifndef OPCODE_H
#define OPCODE_H

enum Opcode
{
    PUSH_STATUS_TO_STACK = 0x08,
    OR_MEMORY_WITH_ACCUMULATOR_ABSOLUTE = 0x0D,
    BRANCH_ON_NEGATIVE_CLEAR = 0x10,
    CLEAR_CARRY_FLAG = 0x18,
    JUMP_ABSOLUTE_SAVE_RETURN = 0x20,
    PULL_STATUS_FROM_STACK = 0x28,
    ABSOLUTE_BITWISE_TEST = 0x2c,
    BRANCH_ON_NEGATIVE_SET = 0x30,
    SHIFT_RIGHT_ACCUMULATOR = 0x4A,
    JUMP_ABSOLUTE = 0x4C,
    PUSH_ACCUMULATOR_TO_STACK = 0x48,
    BRANCH_ON_OVERFLOW_CLEAR = 0x50,
    CLEAR_INTERRUPT_DISABLE = 0x58,
    RETURN_FROM_SUBROUTINE = 0x60,
    PULL_ACCUMULATOR_FROM_STACK = 0x68,
    ADD_IMMEDIATE_WITH_BORROW = 0x69,
    BRANCH_ON_OVERFLOW_SET = 0x70,
    SET_INTERRUPT_DISABLE = 0x78,
    STORE_INDEX_Y_AT_ZERO_PAGE = 0x84,
    STORE_ACCUMULATOR_AT_ZERO_PAGE = 0x85,
    STORE_INDEX_X_AT_ZERO_PAGE = 0x86,
    STORE_ACCUMULATOR_AT_ABSOLUTE = 0x8D,
    DECREMENT_INDEX_Y = 0x88,
    STORE_INDEX_X_AT_ABSOLUTE = 0x8E,
    BRANCH_ON_CARRY_CLEAR = 0x90,
    STORE_ACCUMULATOR_AT_INDIRECT_Y_INDEXED = 0x91,
    STORE_ACCUMULATOR_AT_ZEROPAGE_X_INDEXED = 0x95,
    TRANSFER_INDEX_Y_TO_ACCUMULATOR = 0x98,
    TRANSFER_INDEX_X_TO_STACK_POINTER = 0x9A,
    STORE_ACCUMULATOR_AT_ABSOLUTE_X_INDEXED = 0x9D,
    LOAD_INDEX_Y_WITH_IMMEDIATE = 0xA0,
    LOAD_INDEX_X_WITH_IMMEDIATE = 0xA2,
    LOAD_ACCUMULATOR_WITH_ZERO_PAGE = 0xA5,
    TRANSFER_ACCUMULATOR_TO_INDEX_Y = 0xA8,
    LOAD_ACCUMULATOR_WITH_IMMEDIATE = 0xA9,
    TRANSFER_ACCUMULATOR_TO_INDEX_X = 0xAA,
    BRANCH_ON_CARRY_SET = 0xB0,
    TRANSFER_STACK_POINTER_TO_INDEX_X = 0xBA,
    INCREMENT_INDEX_Y = 0xC8,
    COMPARE_WITH_IMMEDIATE = 0xC9,
    DECREMENT_INDEX_X = 0xCA,
    BRANCH_ON_ZERO_CLEAR = 0xD0,
    CLEAR_DECIMAL_MODE = 0xD8,
    INCREMENT_ZERO_PAGED_ADDRESS = 0xE6,
    INCREMENT_INDEX_X = 0xE8,
    SUBRACT_IMMEDIATE_WITH_BORROW = 0xE9,
    BRANCH_ON_ZERO_SET = 0xF0,
    UNKNOWN_OPCODE,
};

#endif