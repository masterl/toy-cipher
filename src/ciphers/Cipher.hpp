#ifndef CIPHERS_CIPHER_HPP
#define CIPHERS_CIPHER_HPP

#include <string>

class Cipher
{
    public:
    virtual std::string encode( std::string const &text ) const = 0;

    int get_offset( char character, char base ) const
    {
        return character - base;
    }
};

#endif
