#include <iostream>
#include "KeyValueParserFromFile.h"

int main()
{
    ParseFileToVector<std::string, int>("demo.txt", '=');

    return 0;
}
