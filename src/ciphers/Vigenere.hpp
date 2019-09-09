#ifndef CIPHERS_VIGENERE_HPP
#define CIPHERS_VIGENERE_HPP

#include "Cipher.hpp"

class Vigenere : public Cipher
{
    public:
    Vigenere( std::string const key );

    virtual std::string encode( std::string const &text ) const;

    private:
    std::string const key;

    char encode_character( char const ch, char const key_ch ) const;
};

#endif
