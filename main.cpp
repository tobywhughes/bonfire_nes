#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    string fileName;

    if (argc <= 1)
    {
        cout << "Must provide ROM" << endl;
    }

    fileName = argv[1];

    cout << fileName;

    return 0;
}