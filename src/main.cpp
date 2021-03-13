#include <iostream>
#include <algorithm>
#include "KeyValueParserFromFile.h"
// Add header file

int main()
{
    // make specialization and choose separators
    auto out = ParseFileToVector<std::string, int>("demo.txt",'=','\n');

    // Use
    std::cout << "Original data:\n";
    for(auto element : out)
        std::cout << element.first << " = " << element.second << '\n';

    std::cout << "\nNumber is multiply by 3:\n";
    for(auto element : out)
        std::cout << element.first << " = " << element.second * 3 << '\n';

    std::cout << "\nErase 'e' letter from text part and add 5\n";
    for(auto element : out)
    {
        element.first.erase(std::remove(element.first.begin(), element.first.end(), 'E'),
                                         element.first.end());
        std::cout << element.first << " = " << element.second + 5 << '\n';
    }


    return 0;
}
