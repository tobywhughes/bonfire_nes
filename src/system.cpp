#include <iostream>
#include "system.h"
#include "cpu.h"

using namespace std;

System::System(string fileName) : m_memory(fileName),
                                  m_cpu()
{
}

void System::start()
{
    long int opcodesExecuted = 0;

    m_cpu.initialize(m_memory);
    while (true)
    {
        m_cpu.execute(m_memory, opcodesExecuted);
        opcodesExecuted += 1;
    }
}
