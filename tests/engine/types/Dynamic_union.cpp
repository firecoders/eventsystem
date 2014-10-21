/* eventsystem, A generic C++ eventsystem library utilizing templates
   Copyright (c) 2014 firecoders

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE. */

#include <gtest/gtest.h>

#include "engine/types/Dynamic_union.hpp"
#include "engine/types/Type_descriptions.hpp"

#include <string>

using namespace engine::types;

TEST ( engineTypesDynamicUnion, predefinedTypes )
{
    Dynamic_union boolean { true };
    Dynamic_union integer { 42 };
    Dynamic_union doubleFloat { -17.2 };
    Dynamic_union string { std::string ( "Hello World!" ) };

    EXPECT_EQ ( "bool",        boolean.get_type () );
    EXPECT_EQ ( "int",         integer.get_type () );
    EXPECT_EQ ( "double",      doubleFloat.get_type () );
    EXPECT_EQ ( "std::string", string.get_type () );

    EXPECT_EQ ( true, boolean.get < bool > () );
    EXPECT_EQ ( 42, integer.get < int > () );
    EXPECT_EQ ( -17.2, doubleFloat.get < double > () );
    EXPECT_EQ ( std::string ( "Hello World!" ), string.get < std::string > () );

    EXPECT_THROW ( boolean.get < int > (), std::logic_error );
    EXPECT_THROW ( string.get < double > (), std::logic_error );
}

// user defined types

struct Wrap_an_int
{
    int wrapped;
    bool operator== ( const Wrap_an_int& other ) const
    {
        return wrapped == other.wrapped;
    }
    bool operator< ( const Wrap_an_int& other ) const
    {
        return wrapped < other.wrapped;
    }
};

namespace engine
{
    namespace types
    {
        template <>
        struct Type_description < Wrap_an_int >
        {
            static constexpr const char* type_string = "Wrap_an_int";
            static bool operator_equals ( const Dynamic_union& lhs, const Dynamic_union& rhs )
            {
                return lhs.get < Wrap_an_int > () == rhs.get < Wrap_an_int > ();
            }
            static bool operator_less ( const Dynamic_union& lhs, const Dynamic_union& rhs )
            {
                return lhs.get < Wrap_an_int > () < rhs.get < Wrap_an_int > ();
            }
        };
    } /* namespace types */
} /* namespace engine */

TEST ( engineTypesDynamicUnion, userDefinedTypes )
{
    Dynamic_union wrap_an_int ( Wrap_an_int { 213947 } );
    EXPECT_EQ ( "Wrap_an_int", wrap_an_int.get_type () );
    EXPECT_EQ ( Wrap_an_int { 213947 }, wrap_an_int.get < Wrap_an_int > () );
}

TEST ( engineTypesDynamicUnion, operators )
{
    Dynamic_union three ( 3 );
    Dynamic_union four ( 4 );
    Dynamic_union also_four ( 4 );
    Dynamic_union false_ ( false );
    Dynamic_union true_ ( true );
    EXPECT_TRUE ( three == three );
    EXPECT_FALSE ( three == true_ );
    EXPECT_TRUE ( four == also_four );
    EXPECT_FALSE ( false_ == true_ );
}
