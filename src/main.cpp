#include <iostream>
#include <algorithm>
#include <iomanip>
#include "KeyValueParserFromFile.h"
// Add header file

int main()
{
    // make specialization and choose separators
    auto out = ParseFileToVector< std::string, float >("demo.txt",'=','\n');

    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    std::cout.precision(3);

    // Use
    std::cout << "Original data:\n";
    for( auto& element : out )
        std::cout << element.first << " \t= " << element.second << '\n';

    std::cout << "\nNumber is devide by 3:\n";
    for( auto& element : out )
        std::cout << element.first << " \t= " << element.second / 3 << '\n';

    std::cout << "\nErase 'e' letter from text part and add 5.6\n";
    for( auto& element : out )
    {
        element.first.erase( std::remove( element.first.begin(), element.first.end(), 'E' ),
                                         element.first.end() );
        std::cout << element.first << " \t= " << element.second + 5.6 << '\n';
    }

    return 0;
}
