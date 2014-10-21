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

#include "engine/types/Dict.h"

using namespace engine::types;

Dict_element::Dict_element () :
    type ( Type::empty )
{}

Dict_element::Dict_element ( std::shared_ptr< Dict > dict ) :
    type ( Type::dict ),
    value ( std::make_shared< std::shared_ptr< Dict > > ( dict ) )
{}

Dict_element::Dict_element ( std::shared_ptr< std::vector< Dict_element > > vector ) :
    type ( Type::vector ),
    value ( std::make_shared< std::shared_ptr< std::vector< Dict_element > > > ( vector ) )
{}

Dict_element::Dict_element ( const std::string&& string ) :
    type ( Type::string ),
    value ( std::make_shared< std::string > ( string ) )
{}

Dict_element::Dict_element ( sf::RenderTarget* rendertarget ) :
    type ( Type::rendertarget ),
    value ( std::make_shared< sf::RenderTarget* > ( rendertarget ) )
{}

Dict_element::Dict_element ( int integer ) :
    type ( Type::integer ),
    value ( std::make_shared< int > ( integer ) )
{}

Dict_element::Dict_element ( uint32_t uint32 ) :
    type ( Type::uint32 ),
    value ( std::make_shared< uint32_t > ( uint32 ) )
{}

Dict_element::Dict_element ( float floating ) :
    type ( Type::floating ),
    value ( std::make_shared< float > ( floating ) )
{}

Dict_element::Dict_element ( bool boolean ) :
    type ( Type::boolean ),
    value ( std::make_shared< bool > ( boolean ) )
{}


Type Dict_element::get_type () const
{
    return type;
}

bool Dict_element::operator< ( const Dict_element& other ) const
{
    if ( type != other.type )
    {
        return type < other.type;
    }
    switch ( type )
    {
        case Type::string:
            return string () < other.string ();
        case Type::uint32:
            return uint32 () < other.uint32 ();
        case Type::integer:
            return integer () < other.integer ();
        case Type::floating:
            return floating () < other.floating ();
        case Type::boolean:
            return boolean () < other.boolean ();
        case Type::rendertarget:
            return rendertarget () < other.rendertarget ();
        case Type::dict:
            return dict () < other.dict ();
        case Type::vector:
            return vector () < other.vector ();
        case Type::empty:
            return false;
    }
    return false;
}

bool Dict_element::operator== ( const Dict_element& other ) const
{
    if ( type != other.type )
    {
        return false;
    }
    switch ( type )
    {
        case Type::string:
            return string () == other.string ();
        case Type::uint32:
            return uint32 () == other.uint32 ();
        case Type::integer:
            return integer () == other.integer ();
        case Type::floating:
            return floating () == other.floating ();
        case Type::boolean:
            return boolean () == other.boolean ();
        case Type::rendertarget:
            return rendertarget () == other.rendertarget ();
        case Type::dict:
            return dict () == other.dict ();
        case Type::vector:
            return vector () == other.vector ();
        case Type::empty:
            return true;
    }
    return false;
}

const std::map< Type, std::string > strings
{
    { Type::dict, "dict" },
    { Type::vector, "vector" },
    { Type::rendertarget, "rendertarget" },
    { Type::string, "string" },
    { Type::integer, "integer" },
    { Type::uint32, "uint32" },
    { Type::floating, "floating" },
    { Type::boolean, "boolean" },
    { Type::empty, "empty" }
};

void check_type ( Type actual, Type check )
{
    if ( actual != check )
    {
        throw std::logic_error ( "Cannot retrieve " + strings.at ( check ) +
                " from a Dict_element whose type is " + strings.at ( actual ) + "." );
    }
}


std::shared_ptr< Dict > Dict_element::dict () const
{
    check_type ( type, Type::dict );
    return * ( ( std::shared_ptr< Dict >* ) value.get () );
}

std::shared_ptr< std::vector< Dict_element > > Dict_element::vector () const
{
    check_type ( type, Type::vector );
    return * ( ( std::shared_ptr< std::vector< Dict_element > >* ) value.get () );
}

std::string& Dict_element::string () const
{
    check_type ( type, Type::string );
    return * ( ( std::string* ) value.get () );
}

sf::RenderTarget* Dict_element::rendertarget () const
{
    check_type ( type, Type::rendertarget );
    return * ( ( sf::RenderTarget** ) value.get () );
}

int Dict_element::integer () const
{
    check_type ( type, Type::integer );
    return * ( ( int* ) value.get () );
}

uint32_t Dict_element::uint32 () const
{
    check_type ( type, Type::uint32 );
    return * ( ( uint32_t* ) value.get () );
}

float Dict_element::floating () const
{
    check_type ( type, Type::floating );
    return * ( ( float* ) value.get () );
}

bool Dict_element::boolean () const
{
    check_type ( type, Type::boolean );
    return * ( ( bool* ) value.get () );
}


namespace engine
{
    namespace types
    {
        std::ostream& operator<< ( std::ostream& os, const Dict_element& element )
        {
            os << "(" << strings.at ( element.get_type () ) << ") ";
            switch ( element.get_type () )
            {
                case Type::string:
                    os << element.string ();
                    break;
                case Type::uint32:
                    os << element.uint32 ();
                    break;
                case Type::integer:
                    os << element.integer ();
                    break;
                case Type::floating:
                    os << element.floating ();
                    break;
                case Type::boolean:
                    os << element.boolean ();
                    break;
                case Type::rendertarget:
                    os << element.rendertarget ();
                    break;
                case Type::dict:
                    os << element.dict ();
                    break;
                case Type::vector:
                    os << element.vector ();
                    break;
                case Type::empty:
                    break;
            }
            return os;
        }

        std::ostream& operator<< ( std::ostream& os, const std::pair< Dict_element, Dict_element >& key_value_pair )
        {
            os << key_value_pair.first << " -> " << key_value_pair.second;
            return os;
        }

        std::ostream& operator<< ( std::ostream& os, const std::vector< Dict_element >& vector )
        {
            os << "[ ";
            std::copy ( vector.begin(), vector.end(),
                    std::ostream_iterator< Dict_element > ( os, ", " ) );
            os << "]";
            return os;
        }

        std::ostream& operator<< ( std::ostream& os, const Dict& dict )
        {
            std::copy ( dict.begin(), dict.end(),
                    std::ostream_iterator< std::pair< Dict_element, Dict_element > > ( os, "\n" ) );
            return os;
        }
    } /* namespace types */
} /* namespace engine */
