#include <iostream>
#include <fstream>
#include <string>

#include "rom.h"

using namespace std;

int main(int argc, char **argv)
{
    string fileName;

    if (argc <= 1)
    {
        cout << "Must provide ROM" << endl;
        return 0;
    }

    fileName = argv[1];

    Rom rom(fileName);

    rom.printTest();

    return 0;
}