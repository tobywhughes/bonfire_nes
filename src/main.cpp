#include <iostream>
#include <fstream>
#include <string>

#include "rom.h"

using namespace std;

string getFileNameFromArgs(int, char **);

int main(int argc, char **argv)
{
    string fileName = getFileNameFromArgs(argc, argv);

    Rom rom(fileName);

    rom.printTest();

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