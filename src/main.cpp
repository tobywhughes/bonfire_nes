#include <iostream>
#include <fstream>
#include <string>

#include "memory.h"
#include "cpu.h"

using namespace std;

string getFileNameFromArgs(int, char **);

int main(int argc, char **argv)
{
    string fileName = getFileNameFromArgs(argc, argv);

    Memory memory(fileName);

    cout << "Test reset vector: 0x" << hex << (int)memory.read8(RESET_VECTOR_ADDRESS) << endl;
    cout << "Test unmapped: 0x" << hex << (int)memory.read8(0x7FFF) << endl;

    return 0;
}

string getFileNameFromArgs(int argc, char **argv)
{
    if (argc <= 1)
    {
        cout << "Must provide ROM" << endl;
        exit(0);
    }

    return argv[1];
}