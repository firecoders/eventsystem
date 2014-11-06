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

#ifndef ENGINE_TYPES_DYNAMIC_UNION_GUARD
#define ENGINE_TYPES_DYNAMIC_UNION_GUARD

#include <stdexcept>
#include <memory>
#include <string>
#include <functional>

namespace engine
{
    namespace types
    {
        template < typename T >
        struct Type_description {};

        class Dynamic_union
        {
            public:
                template < typename T >
                Dynamic_union ( T value );

                std::string get_type () const;
                bool operator== ( const Dynamic_union& other ) const;
                bool operator< ( const Dynamic_union& other ) const;

                template < typename T >
                T get () const;

            private:
                typedef std::function < bool ( const Dynamic_union&, const Dynamic_union& ) > Compare_function;

                std::string type;
                std::shared_ptr < void > value;
                Compare_function operator_equals;
                Compare_function operator_less;

                void check_type ( std::string type ) const;
        };

        template < typename T >
        Dynamic_union::Dynamic_union ( T val ) :
            type ( Type_description < T >::type_string ),
            value ( std::make_shared < T > ( val ) ),
            operator_equals ( Compare_function ( Type_description < T >::operator_equals ) ),
            operator_less ( Compare_function ( Type_description < T >::operator_less ) )
        {}

        inline std::string Dynamic_union::get_type () const
        {
            return type;
        }

        inline bool Dynamic_union::operator== ( const Dynamic_union& other ) const
        {
            if ( get_type () != other.get_type () )
            {
                return false;
            }
            return operator_equals ( *this, other );
        }

        inline bool Dynamic_union::operator< ( const Dynamic_union& other ) const
        {
            if ( get_type () != other.get_type () )
            {
                return get_type () < other.get_type ();
            }
            return operator_less ( *this, other );
        }

        template < typename T >
        T Dynamic_union::get () const
        {
            check_type ( Type_description < T >::type_string );
            return * ( ( T* ) value.get () );
        }

        inline void Dynamic_union::check_type ( std::string type ) const
        {
             if ( get_type () != type )
             {
                 throw std::logic_error ( "Cannot retrieve " + type +
                         " from a Dynamic_union whose type is " + get_type () + "." );
             }
        }

    } /* namespace types */
} /* namespace engine */

#endif // ENGINE_TYPES_DYNAMIC_UNION_GUARD
