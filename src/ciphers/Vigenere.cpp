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
        letter = encode_character( letter, key[key_index] );

        ++key_index;
        key_index %= key.length();
    }

    return encoded;
}

void Vigenere::encode( std::istream &istream, std::ostream &ostream ) const
{
    int key_index{0};
    char letter;

    while( istream.good() )
    {
        istream >> letter;

        if( istream.good() )
        {
            ostream << encode_character( letter, key[key_index] );
        }

        ++key_index;
        key_index %= key.length();
    }
}

char Vigenere::encode_character( char const ch, char const key_ch ) const
{
    if( !isalpha( ch ) )
    {
        return ch;
    }

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
