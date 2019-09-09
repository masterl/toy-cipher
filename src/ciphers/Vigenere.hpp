#ifndef CIPHERS_VIGENERE_HPP
#define CIPHERS_VIGENERE_HPP

#include "Cipher.hpp"

class Vigenere : public Cipher
{
    public:
    Vigenere( std::string const key );

    virtual std::string encode( std::string const &text ) const;
    virtual void encode( std::istream &istream, std::ostream &ostream ) const;

    std::string get_key() const
    {
        return key;
    }

    private:
    std::string key;

    char encode_character( char const ch, char const key_ch ) const;
    void normalize_key();
};

#endif
