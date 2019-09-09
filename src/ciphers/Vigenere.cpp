#include "Vigenere.hpp"

Vigenere::Vigenere( std::string const key )
    : key{key}
{
}

std::string Vigenere::encode( std::string const &text ) const
{
    int key_index{0};
    std::string encoded{text};
    char const base{'a'};

    for( auto &letter : encoded )
    {
        int const letter_offset{this->get_offset( letter, base )};
        int const key_offset{this->get_offset( key[key_index], base )};

        letter = ( letter_offset + key_offset ) % 26;
        letter += base;

        ++key_index;
        key_index %= key.length();
    }

    return encoded;
}
