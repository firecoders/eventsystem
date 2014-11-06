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

#ifndef ENGINE_TYPES_INDEX_NODE_GUARD
#define ENGINE_TYPES_INDEX_NODE_GUARD

#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

namespace engine
{
    namespace types
    {
        template < typename Wrapped, typename Key = std::string >
            class Index_node {
                public:
                    Index_node ();

                    Index_node < Wrapped, Key >& operator[] ( Key key );
                    std::shared_ptr < Index_node < Wrapped, Key > > at ( Key key );

                    std::shared_ptr < Index_node < Wrapped, Key > > get_descendant ( std::vector < Key > keys );
                    template < typename Iterator >
                    std::shared_ptr < Index_node < Wrapped, Key > > get_descendant ( Iterator keys_begin, Iterator keys_end );

                    std::shared_ptr < Wrapped > get_wrapped () const;
                    void set_wrapped ( std::shared_ptr < Wrapped > wrapped );

                    virtual ~Index_node () = default;

                private:
                    std::map < Key, std::shared_ptr < Index_node < Wrapped, Key > > > children;
                    std::shared_ptr < Wrapped > wrapped;

            };

        template < typename Wrapped, typename Key >
            Index_node < Wrapped, Key >::Index_node () :
                wrapped ( nullptr )
            {}

        template < typename Wrapped, typename Key >
            Index_node < Wrapped, Key >& Index_node < Wrapped, Key >::operator[] ( Key key )
            {
                return * at ( key );
            }

        template < typename Wrapped, typename Key >
            std::shared_ptr < Index_node < Wrapped, Key > > Index_node < Wrapped, Key >::at ( Key key )
            {
                auto iterator = children.find ( key );
                if ( iterator == children.end () )
                {
                    auto node = std::make_shared < Index_node < Wrapped, Key > > ();
                    children.insert ( { key, node } );
                    return node;
                }
                else
                {
                    return iterator->second;
                }
            }

        template < typename Wrapped, typename Key >
            std::shared_ptr < Index_node < Wrapped, Key > > Index_node < Wrapped, Key >::get_descendant ( std::vector < Key > keys )
            {
                return get_descendant ( keys.begin (), keys.end () );
            }

        template < typename Wrapped, typename Key >
        template < typename Iterator >
            std::shared_ptr < Index_node < Wrapped, Key > > Index_node < Wrapped, Key >::get_descendant ( Iterator keys_begin, Iterator keys_end )
            {
                Key key = * keys_begin;
                auto child = at ( key );
                if ( ++keys_begin == keys_end )
                {
                    return child;
                }
                else
                {
                    return child->get_descendant ( keys_begin, keys_end );
                }
            }

        template < typename Wrapped, typename Key >
            std::shared_ptr < Wrapped > Index_node < Wrapped, Key >::get_wrapped () const
            {
                return wrapped;
            }

        template < typename Wrapped, typename Key >
            void Index_node < Wrapped, Key >::set_wrapped ( std::shared_ptr < Wrapped > wrapped )
            {
                this->wrapped = wrapped;
            }

    } /* namespace types */
} /* namespace engine */

#endif // ENGINE_TYPES_INDEX_NODE_GUARD
