/* eventsystem, A generic C++ eventsystem library utilizing templates
   Copyright (C) 2014 firecoders

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
   OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef ENGINE_TYPES_DICT_GUARD
#define ENGINE_TYPES_DICT_GUARD

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <algorithm>

namespace sf
{
    class RenderTarget;
} /* namespace sf */

namespace engine
{
    namespace types
    {
        class Dict_element;

        typedef std::map< Dict_element, Dict_element > Dict;

        enum class Type
        {
            string, integer, uint32, floating, boolean, rendertarget, dict, vector, empty
        };

        class Dict_element
        {
            public:
                Dict_element ();
                Dict_element ( std::shared_ptr< Dict > dict );
                Dict_element ( std::shared_ptr< std::vector< Dict_element > > vector );
                Dict_element ( const std::string&& string );
                Dict_element ( sf::RenderTarget* rendertarget );
                Dict_element ( int integer );
                Dict_element ( uint32_t integer );
                Dict_element ( float floating );
                Dict_element ( bool boolean );

                Type get_type () const;
                bool operator< ( const Dict_element& other ) const;
                bool operator== ( const Dict_element& other ) const;

                std::shared_ptr< Dict > dict () const;
                std::shared_ptr< std::vector< Dict_element > > vector () const;
                std::string& string () const;
                sf::RenderTarget* rendertarget () const;
                int integer () const;
                uint32_t uint32 () const;
                float floating () const;
                bool boolean () const;

            private:
                Type type;
                std::shared_ptr< void > value;
        };

        std::ostream& operator<< ( std::ostream& os, const Dict_element& element );
        std::ostream& operator<< ( std::ostream& os, const std::pair< Dict_element, Dict_element >& key_value_pair );
        std::ostream& operator<< ( std::ostream& os, const std::vector< Dict_element >& vector );
        std::ostream& operator<< ( std::ostream& os, const Dict& dict );

    } /* namespace types */
} /* namespace engine */

#endif // ENGINE_TYPES_DICT_GUARD
