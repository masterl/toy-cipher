#include <iostream>
#include <map>

#include "ciphers/Vigenere.hpp"

using ProgramOptions = std::map< std::string, std::string >;

ProgramOptions extract_options( int const argc, char const *argv[] );

int main( int const argc, char const *argv[] )
{
    ProgramOptions const options{extract_options( argc, argv )};

    auto it = options.find( "-f" );

    if( it == options.end() )
    {
        // cin
        Vigenere cipher = Vigenere( "key" );

        std::cin.unsetf( std::ios::skipws );
        cipher.encode( std::cin, std::cout );
    }
    else
    {
        // file
        // std::ifstream file....
        // Cipher.encode(file)
    }

    return 0;
}

ProgramOptions extract_options( int const argc, char const *argv[] )
{
    ProgramOptions options;

    bool flag{true};
    std::string last_param;

    for( int i{1}; i < argc; ++i )
    {
        std::string const param{argv[i]};

        if( flag )
        {
            options[param] = "";

            if( param.substr( 0, 2 ) != "--" )
            {
                flag = false;
            }
        }
        else
        {
            options[last_param] = param;

            flag = true;
        }

        last_param = param;
    }

    return options;
}
