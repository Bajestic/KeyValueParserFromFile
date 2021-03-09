#ifndef KEYVALUEPARSERFROMFILE_H_
#define KEYVALUEPARSERFROMFILE_H_

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <type_traits>

// TODO: Make struct of bools to easly manage types
// TODO: More static assertions for type control to choose overload function for strict types
// TODO: Extract data to containers - map and vector of pairs
// TODO: Static_assert vs Enable_if, which better for multiply clarifications types ?
// TODO: Tests and exceptions...

template< typename key_type, typename values_type >
std::vector<std::pair< key_type, values_type >> ParseFileToVector(std::string filename, const char assigment_separator = '=', const char separator = '\n')
{
    static_assert( std::is_same< key_type, std::string >::value &&
                   std::is_same< values_type,   int >::value,
                   "Key type is not a string type or value type is not a int type\n" );

//    bool key_type_is_string = std::is_same< key_type, std::string >::value;

    if( std::is_same< key_type, std::string >::value && std::is_same< values_type, int >::value )
    {
        std::ifstream parse_file(filename, std::ios::in);
        std::vector<std::pair<key_type,values_type>> vec;
        const char sep = separator;
        key_type key{};
        values_type values{};
        if(parse_file.is_open())
        {
            std::string temp;
            temp.assign( std::istreambuf_iterator<char>(parse_file), std::istreambuf_iterator<char>() );
            char * fileTemp = new char[temp.length() + 1];
            strcpy( fileTemp,temp.c_str() );
            char * token = strtok(fileTemp, &assigment_separator);
            std::cout << token;
            while( token != NULL )
            {
                // control message, replace std::cout with push_back()
                std::cout << token << '\n';
                token = std::strtok( NULL, "=\n" );
            }
            delete [] fileTemp;
        }
        else
        {
            std::cerr << "File not found\n";
            return vec;
        }

        parse_file.close();
        return vec;
    }
    else
    {
        std::cerr << "Fail";
        std::vector<std::pair<key_type,values_type>> vec;
        return vec;
    }
}

#endif // KEYVALUEPARSERFROMFILE_H_

