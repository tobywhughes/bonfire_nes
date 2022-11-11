#include "rom.h"
#include <iostream>
#include <fstream>

using namespace std;

Rom::Rom(string fileName)
{
    cout << "ROM Filename: " << fileName << endl;
    ifstream file(fileName, ios::binary);
    buffer = vector<unsigned char>(istreambuf_iterator<char>(file), {});
    file.close();
}

void Rom::printTest()
{
    cout << buffer[0] << buffer[1] << buffer[2] << endl;
}