#ifndef ATOALL_H_
#define ATOALL_H_

/*
/ atoall() function is a templatized version of std library convert functions from char * to numeric type
/ use as atoall< return_type >( char * )
*/

#include <cstdlib>

// TODO: More specializations for int, long and float double etc. for optimation memory

template< typename T >
static T atoallimp( char * str, std::true_type )
{
    static_assert( !( std::is_same< T, wchar_t >::value ), "Convert from char types not allowed");
    return atol( str );
}

template< typename T >
static T atoallimp( char * str, std::false_type )
{
    return atof( str );
}

template< typename T >
T atoall( char * str )
{
    return atoallimp< T >( str, std::is_integral< T >() );
}

#endif // ATOALL_H_
