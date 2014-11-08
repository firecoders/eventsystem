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

#include <string>

using namespace engine::types;

template < typename T >
    struct Type_description {};

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

template <>
    struct Type_description < Wrap_an_int >
    {
        static constexpr const char* type_string = "Wrap_an_int";
        static bool operator_equals ( const Dynamic_union < Type_description >& lhs, const Dynamic_union < Type_description >& rhs )
        {
            return lhs.get < Wrap_an_int > () == rhs.get < Wrap_an_int > ();
        }
        static bool operator_less ( const Dynamic_union < Type_description >& lhs, const Dynamic_union < Type_description >& rhs )
        {
            return lhs.get < Wrap_an_int > () < rhs.get < Wrap_an_int > ();
        }
    };

TEST ( engineTypesDynamicUnion, exampleType )
{
    Dynamic_union < Type_description > wrap_an_int ( Wrap_an_int { 213947 } );
    EXPECT_EQ ( "Wrap_an_int", wrap_an_int.get_type () );
    EXPECT_EQ ( Wrap_an_int { 213947 }, wrap_an_int.get < Wrap_an_int > () );
}

TEST ( engineTypesDynamicUnion, operators )
{
    Dynamic_union < Type_description > three ( Wrap_an_int { 3 } );
    Dynamic_union < Type_description > four ( Wrap_an_int { 4 } );
    Dynamic_union < Type_description > also_four ( Wrap_an_int { 4 } );
    EXPECT_TRUE ( three == three );
    EXPECT_TRUE ( four == also_four );
    EXPECT_TRUE ( three < four );
    EXPECT_FALSE ( four < also_four );
    EXPECT_FALSE ( four < three );
}
