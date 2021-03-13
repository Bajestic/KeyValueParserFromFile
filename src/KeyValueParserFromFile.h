#ifndef KEYVALUEPARSERFROMFILE_H_
#define KEYVALUEPARSERFROMFILE_H_

/*
/ Key Value Parser From File is one header file which add parser
/ functions for you project to extract data from file to containers.
/ To use call ParseFileToVector() function and make template specialization
/ depending on the types to be guessed from file.
/ (ParseFileToOtherContainers() functions in progress)
/ It is also possible to choose two separators - 'assigment separator',
/ connect key and value in pair and 'separator' to split next key-value pair.
/ Default separators are respectively '=' for assigment separator
/ and next line tag '\n' for separator
*/

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <type_traits>

// TODO: More static assertions for type control to choose overload function for strict types
// TODO: Extract data to containers - map and vector of pairs for more types
// TODO: Static_assert vs Enable_if, which better for multiply clarifications types ?
// TODO: Exceptions in case of bad format source file (repeated separators)
// TODO: Tests...

template< typename key_type, typename values_type >
std::vector<std::pair< key_type, values_type >> ParseFileToVector(std::string filename,
            const char assigment_separator = '=', const char separator = '\n')
{
    // for now only support <std::string, int>
    const bool key_type_is_string     = std::is_same< key_type, std::string >::value;
    const bool value_type_is_int      = std::is_same< values_type, int >::value;
    static_assert( key_type_is_string && value_type_is_int, "Unsupported types" );
}

template<>
std::vector<std::pair< std::string, int >> ParseFileToVector(std::string filename,
            const char assigment_separator, const char separator)
{
    std::ifstream parse_file(filename, std::ios::in);
    std::vector<std::pair<std::string,int>> vec;
    std::pair<std::string,int> pair_temp{};
    std::string key_temp{};
    int values_temp{};
    char sepeparators[2] = { assigment_separator, separator };
    bool key_value_switcher = true;

    if(parse_file.is_open())
    {
        std::string temp;
        temp.assign( std::istreambuf_iterator<char>(parse_file), std::istreambuf_iterator<char>() );
        char * fileTemp = new char[temp.length() + 1];
        strcpy( fileTemp,temp.c_str() );
        char * token = strtok(fileTemp, &assigment_separator);
        while( token != NULL )
        {
            if( key_value_switcher )
            {
                pair_temp.first = token;
                key_value_switcher = false;
            }
            else
            {
                pair_temp.second = atoi(token);
                vec.push_back(pair_temp);
                key_value_switcher = true;
            }

            token = std::strtok( NULL, sepeparators );
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

#endif // KEYVALUEPARSERFROMFILE_H_

