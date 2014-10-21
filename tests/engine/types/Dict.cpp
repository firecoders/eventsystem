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

#include <iostream>
#include <exception>
#include <memory>
#include <vector>
#include "engine/types/Dict.h"

using namespace engine::types;

TEST ( engineTypesDict, operatorEquals ) {
    Dict false2true { { false, true } };
    Dict true2false { { true, false } };
    EXPECT_EQ ( false2true, false2true );
    EXPECT_EQ ( true2false, true2false );
    EXPECT_NE ( false2true, true2false );
    EXPECT_NE ( true2false, false2true );
}

TEST ( engineTypesDict, dictType )
{
    std::shared_ptr< Dict > key_dict, value_dict = std::make_shared< Dict > ();
    Dict dict  { { key_dict, value_dict } };
    EXPECT_EQ ( value_dict, dict.at ( key_dict ).dict () );

    std::shared_ptr< Dict > sub_key, sub_value = std::make_shared< Dict > ();
    std::shared_ptr< Dict > subdict = dict.at ( key_dict ). dict ();

    subdict->insert ( { sub_key, sub_value } );
    EXPECT_EQ ( sub_value, dict.at ( key_dict ).dict ()->at ( sub_key ).dict () );

    EXPECT_THROW ( ( Dict_element {} ).dict (), std::logic_error );
}

TEST ( engineTypesDict, vectorType )
{
    std::shared_ptr< std::vector< Dict_element > > key_vector, value_vector = std::make_shared< std::vector< Dict_element > > ();
    Dict dict { { key_vector, value_vector } };
    EXPECT_EQ ( value_vector, dict.at ( key_vector ).vector () );

    std::shared_ptr< std::vector< Dict_element > > sub_value = std::make_shared< std::vector< Dict_element > > ();
    std::shared_ptr< std::vector< Dict_element > > subvector = dict.at ( key_vector ).vector ();

    subvector->push_back ( sub_value );
    EXPECT_EQ ( sub_value, dict.at ( key_vector ).vector ()->at ( 0 ).vector () );

    EXPECT_THROW ( ( Dict_element {} ).vector (), std::logic_error );
}

TEST ( engineTypesDict, stringType )
{
    Dict dict   { { std::string ( "key1" ), std::string ( "val1" ) } };
    dict.insert ( { std::string ( "key2" ), std::string ( "val2" ) } );
    EXPECT_EQ ( std::string ( "val1" ), dict.at ( std::string ( "key1" ) ).string () );
    EXPECT_EQ ( std::string ( "val2" ), dict.at ( std::string ( "key2" ) ).string () );
    EXPECT_THROW ( ( Dict_element {} ).string (), std::logic_error );
}

TEST ( engineTypesDict, rendertargetType )
{
    EXPECT_THROW ( ( Dict_element {} ).rendertarget (), std::logic_error );
}

TEST ( engineTypesDict, integerType )
{
    Dict dict   { { int ( 1 ), int ( 2 ) } };
    dict.insert ( { int ( 2 ), int ( 3 ) } );
    EXPECT_EQ ( int ( 2 ), dict.at ( int ( 1 ) ).integer () );
    EXPECT_EQ ( int ( 3 ), dict.at ( int ( 2 ) ).integer () );
    EXPECT_THROW ( ( Dict_element {} ).integer (), std::logic_error );
}

TEST ( engineTypesDict, uint32Type )
{
    Dict dict   { { uint32_t ( 1 ), uint32_t ( 2 ) } };
    dict.insert ( { uint32_t ( 2 ), uint32_t ( 3 ) } );
    EXPECT_EQ ( uint32_t ( 2 ), dict.at ( uint32_t ( 1 ) ).uint32 () );
    EXPECT_EQ ( uint32_t ( 3 ), dict.at ( uint32_t ( 2 ) ).uint32 () );
    EXPECT_THROW ( ( Dict_element {} ).uint32 (), std::logic_error );
}

TEST ( engineTypesDict, floatingType )
{
    Dict dict   { { float ( 1 ), float ( 2 ) } };
    dict.insert ( { float ( 2 ), float ( 3 ) } );
    EXPECT_EQ ( float ( 2 ), dict.at ( float ( 1 ) ).floating () );
    EXPECT_EQ ( float ( 3 ), dict.at ( float ( 2 ) ).floating () );
    EXPECT_THROW ( ( Dict_element {} ).floating (), std::logic_error );
}

TEST ( engineTypesDict, booleanType )
{
    Dict dict   { { false, true } };
    dict.insert ( { true, false } );
    EXPECT_EQ ( false, dict.at ( true ).boolean () );
    EXPECT_EQ ( true, dict.at ( false ).boolean () );
    EXPECT_THROW ( ( Dict_element {} ).boolean (), std::logic_error );
}
