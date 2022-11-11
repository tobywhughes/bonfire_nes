#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    cout << fileName << endl;

    ifstream file(fileName, ios::binary);
    vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});
    file.close();

    return 0;
}