#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <string>
#include <sstream>

// number to string conversions

template< typename T >
std::string NumberToString( T Number )
{
    std::stringstream out;
    out << Number;
    return out.str();
};

template< typename T >
std::wstring NumberToWideString( T Number )
{
    std::wstringstream out;
    out << Number;
    return out.str();
};

#endif