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

#include <string>
#include <memory>
#include <map>

#include "engine/types/Dynamic_union.hpp"

namespace engine
{
    namespace types
    {
        template < typename T >
            struct Dict_types {};

        typedef std::map < std::string, Dynamic_union < Dict_types > > Dict;

        template <>
            struct Dict_types < bool >
            {
                static constexpr const char* type_string = "bool";
                static bool operator_equals ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < bool > () == rhs.get < bool > ();
                }
                static bool operator_less ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < bool > () < rhs.get < bool > ();
                }
            };

        template <>
            struct Dict_types < int >
            {
                static constexpr const char* type_string = "int";
                static bool operator_equals ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < int > () == rhs.get < int > ();
                }
                static bool operator_less ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < int > () < rhs.get < int > ();
                }
            };

        template <>
            struct Dict_types < double >
            {
                static constexpr const char* type_string = "double";
                static bool operator_equals ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < double > () == rhs.get < double > ();
                }
                static bool operator_less ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < double > () < rhs.get < double > ();
                }
            };

        template <>
            struct Dict_types < std::string >
            {
                static constexpr const char* type_string = "std::string";
                static bool operator_equals ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < std::string > () == rhs.get < std::string > ();
                }
                static bool operator_less ( const Dynamic_union < Dict_types >& lhs, const Dynamic_union < Dict_types >& rhs )
                {
                    return lhs.get < std::string > () < rhs.get < std::string > ();
                }
            };
    } /* namespace types */
} /* namespace engine */

#endif // ENGINE_TYPES_DICT_GUARD
