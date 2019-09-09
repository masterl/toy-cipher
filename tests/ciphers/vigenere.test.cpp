#include <catch/catch.hpp>

#include "ciphers/Vigenere.hpp"

SCENARIO( "ciphing using vigenere", "[vigenere]" )
{
    GIVEN( "A sample text and a key" )
    {
        string const text{"sample"};
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

    GIVEN( "A text containing non-alphabetical characters and a key" )
    {
        string const text{"a 123"};
        string const key{"key"};

        THEN( "It should ignore non-alpha characters" )
        {
            Vigenere const vigenere{key};

            string const ciphered{vigenere.encode( text )};

            REQUIRE( ciphered[1] == text[1] );
            REQUIRE( ciphered[2] == text[2] );
            REQUIRE( ciphered[3] == text[3] );
            REQUIRE( ciphered[4] == text[4] );
        }
    }

    GIVEN( "A key containing upper case letters" )
    {
        string const key{"Key"};

        THEN( "It should convert them to lower case" )
        {
            Vigenere const vigenere{key};

            REQUIRE( vigenere.get_key()[0] == 'k' );
        }
    }

    GIVEN( "A text containing upper case letters" )
    {
        string const text{"SamPle"};
        string const key{"key"};

        THEN( "It should encode uppercase characters correctly" )
        {
            Vigenere const vigenere{key};

            std::string const encoded{vigenere.encode( text )};

            REQUIRE( encoded[0] == 'C' );
            REQUIRE( encoded[3] == 'Z' );
        }
    }

    GIVEN( "A text stream" )
    {
        string const text{"sample"};
        string const key{"key"};

        THEN( "It should encode correctly" )
        {
            string const expected{"cekzpc"};

            Vigenere const vigenere{key};

            istringstream istream;
            ostringstream ostream;

            istream.str( text );

            vigenere.encode( istream, ostream );

            REQUIRE( ostream.str() == expected );
        }
    }
}
