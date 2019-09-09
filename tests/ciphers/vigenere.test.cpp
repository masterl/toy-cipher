#include <catch/catch.hpp>

#include "ciphers/Vigenere.hpp"

SCENARIO( "ciphing using vigenere", "[vigenere]" )
{
    GIVEN( "A sample text and a key" )
    {
        string const text{"sample text"};
        string const key{"key"};

        THEN( "It should encode the text" )
        {
            Vigenere const vigenere{key};

            string const ciphered{vigenere.encode( text )};

            REQUIRE( ciphered != text );
        }

        THEN( "It should have ciphered using vigenere algorithm" )
        {
            Vigenere const vigenere{key};

            string const ciphered{vigenere.encode( text )};

            int const text_first{text[0] - 'a'};
            int const key_first{key[0] - 'a'};
            char const expected_char{( ( key_first + text_first ) % 26 ) + 'a'};

            REQUIRE( ciphered[0] == expected_char );
        }
    }
}
