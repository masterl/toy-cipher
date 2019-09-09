#include "Vigenere.hpp"

#include <cctype>

Vigenere::Vigenere( std::string const key )
    : key{key}
{
    normalize_key();
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
    char const lower_base{'a'};
    char const upper_base{'A'};

    char base{lower_base};

    if( isupper( ch ) )
    {
        base = upper_base;
    }

    int const letter_offset{this->get_offset( ch, base )};
    int const key_offset{this->get_offset( key_ch, lower_base )};

    int const encoded_offset{( letter_offset + key_offset ) % 26};

    return encoded_offset + base;
}

void Vigenere::normalize_key()
{
    for( auto &letter : this->key )
    {
        letter = tolower( letter );
    }
}
