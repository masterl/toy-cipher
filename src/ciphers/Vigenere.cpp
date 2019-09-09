#include "Vigenere.hpp"

#include <cctype>

Vigenere::Vigenere( std::string const key )
    : key{key}
{
}

std::string Vigenere::encode( std::string const &text ) const
{
    int key_index{0};
    std::string encoded{text};

    for( auto &letter : encoded )
    {
        if( isalpha( letter ) )
        {
            letter = encode_character( letter, key[key_index] );
        }

        ++key_index;
        key_index %= key.length();
    }

    return encoded;
}

char Vigenere::encode_character( char const ch, char const key_ch ) const
{
    char const base{'a'};

    int const letter_offset{this->get_offset( ch, base )};
    int const key_offset{this->get_offset( key_ch, base )};

    int const encoded_offset{( letter_offset + key_offset ) % 26};

    return encoded_offset + base;
}
