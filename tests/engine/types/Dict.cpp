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

#include <type_traits>
#include <map>
#include <string>

#include "engine/types/Dict.hpp"
#include "engine/types/Dynamic_union.hpp"

using namespace engine::types;

TEST ( engineTypesDict, type )
{
    bool dict_is_map_from_string_to_dynamic_union =
        std::is_same < Dict, std::map < std::string, Dynamic_union < Dict_types > > >::value;
    EXPECT_TRUE ( dict_is_map_from_string_to_dynamic_union );
}

TEST ( engineTypesDict, predefinedTypes )
{
    Dynamic_union < Dict_types > boolean { true };
    Dynamic_union < Dict_types > integer { 42 };
    Dynamic_union < Dict_types > doubleFloat { -17.2 };
    Dynamic_union < Dict_types > string { std::string ( "Hello World!" ) };

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
