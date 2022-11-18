#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include "memory.h"
#include "cpu.h"

class System
{
private:
    Memory m_memory;
    CPU m_cpu;

public:
    System(std::string fileName);
    void start();
};

#endif