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
#include <stdexcept>

// TODO: More static assertions for type control to choose overload function for strict types
// TODO: Extract data to containers - map and vector of pairs for more types
// TODO: Static_assert vs Enable_if, which better for multiply clarifications types ?
// TODO: Exceptions in case of bad format source file (repeated separators, to big data, values etc)
// TODO: Tests...

void ParseExceptions(const std::exception &);

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
    bool key_value_switcher = true;

    try
    {
        if(parse_file.is_open())
        {
            std::string temp;
            // std::string throws exception if data is to big to assign
            temp.assign( std::istreambuf_iterator<char>(parse_file), std::istreambuf_iterator<char>() );
            char * fileTemp = new char[temp.length() + 1];
            strcpy( fileTemp,temp.c_str() );
            char * token = strtok(fileTemp, &assigment_separator);
            while( token != NULL )
            {
                if( key_value_switcher )
                {
                    pair_temp.first = token;
                    token = std::strtok( NULL, &separator );
                    key_value_switcher = false;
                }
                else
                {
                    pair_temp.second = atoi(token);
                    vec.push_back(pair_temp);
                    token = std::strtok( NULL, &assigment_separator );
                    key_value_switcher = true;

                    // run-time assert to do
                }
            }
            delete [] fileTemp;
            parse_file.close();
        }
        else
            throw std::runtime_error("Unable to open file\n");
    }

    catch(const std::exception & exp)
    {
        ParseExceptions(exp);
    }

    return vec;
}

void ParseExceptions(const std::exception & exp)
{
    auto expType = typeid(exp).name();
    if( expType == typeid(std::length_error).name())
        std::cerr << "Reading file has too big data. Error lenght: " << exp.what() << '\n';
    else if( expType == typeid(std::runtime_error).name())
        std::cerr << exp.what();
}

#endif // KEYVALUEPARSERFROMFILE_H_

