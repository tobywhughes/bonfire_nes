#ifndef ROM_H
#define ROM_H

#include <string>
#include <vector>

class Rom
{
private:
    std::vector<unsigned char> buffer;

public:
    Rom(std::string fileName);
    void printTest();
};

#endif