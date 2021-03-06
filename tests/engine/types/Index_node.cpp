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

#include "engine/types/Index_node.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <type_traits>

using namespace engine::types;

TEST ( engineTypesIndexNode, wrappedStorage )
{
    Index_node < int > base;
    EXPECT_EQ ( nullptr, base.get_wrapped () );
    std::shared_ptr < int > wrapped = std::make_shared < int > ( 42 );
    base.set_wrapped ( wrapped );
    EXPECT_EQ ( wrapped, base.get_wrapped () );
}

TEST ( engineTypesIndexNode, absentCreation )
{
    Index_node < int > base;
    EXPECT_EQ ( nullptr, base [ "hello" ].get_wrapped () );
}

TEST ( engineTypesIndexNode, defaultKey )
{
    bool string_is_default_key = std::is_same < Index_node < int >, Index_node < int, std::string > >::value;
    EXPECT_TRUE ( string_is_default_key );
}

TEST ( engineTypesIndexNode, numbersExample )
{
    Index_node < int > base;
    base [ "odd" ] [ "five" ].set_wrapped ( std::make_shared < int > ( 5 ) );
    base [ "even" ] [ "two" ].set_wrapped ( std::make_shared < int > ( 2 ) );
    EXPECT_EQ ( 5, * ( base [ "odd" ] [ "five" ].get_wrapped () ) );
    EXPECT_EQ ( 2, * ( base [ "even" ] [ "two" ].get_wrapped () ) );
}

TEST ( engineTypesIndexNode, sharedPtrsNumbersExample )
{
    std::shared_ptr < Index_node < int > > base = std::make_shared < Index_node < int > > ();
    base->at ( "odd" )->at ( "five" )->set_wrapped ( std::make_shared < int > ( 5 ) );
    base->at ( "even" )->at ( "two" )->set_wrapped ( std::make_shared < int > ( 2 ) );
    EXPECT_EQ ( 5, * ( base->at ( "odd" )->at ( "five" )->get_wrapped () ) );
    EXPECT_EQ ( 2, * ( base->at ( "even" )->at ( "two" )->get_wrapped () ) );
}

TEST ( engineTypesIndexNode, getDescendant )
{
    std::shared_ptr < Index_node < int > > base = std::make_shared < Index_node < int > > ();
    base->get_descendant ( { "some", "deeply", "nested", "index", "node" } )->set_wrapped ( std::make_shared < int > ( 42 ) );
    EXPECT_EQ ( 42, * ( ( * base ) [ "some" ] [ "deeply" ] [ "nested" ] [ "index" ] [ "node" ].get_wrapped () ) );
}
