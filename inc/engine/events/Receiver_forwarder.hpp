/* 2D-engine, A C++ library wrapping sfml, to be used for 2D games
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

#ifndef ENGINE_EVENTS_RECEIVER_FORWARDER_GUARD
#define ENGINE_EVENTS_RECEIVER_FORWARDER_GUARD

#include <memory>

#include "interfaces/Receiver.h"
#include "Broadcaster.hpp"

namespace engine
{
    namespace events
    {
        template < typename Event_type >
            class Receiver_forwarder : public Receiver < Event_type >
            {
                public:
                    Receiver_forwarder ( std::shared_ptr < Receiver < Event_type > > target );

                    virtual void receive ( Event_type event );
                    void redirect ( std::shared_ptr < Receiver < Event_type > > target );

                    virtual ~Receiver_forwarder () noexcept = default;

                private:
                    std::shared_ptr < Receiver < Event_type > > target;
            };

        template < typename Event_type >
            Receiver_forwarder < Event_type >::Receiver_forwarder ( std::shared_ptr < Receiver < Event_type > > target ) :
                target ( target )
            {}

        template < typename Event_type >
            void Receiver_forwarder < Event_type >::receive ( Event_type event )
            {
                if ( target != nullptr )
                    target->receive ( event );
            }

        template < typename Event_type >
            void Receiver_forwarder < Event_type >::redirect ( std::shared_ptr < Receiver < Event_type > > target )
            {
                this->target = target;
            }
    } /* namespace events */
} /* namespace engine */

#endif // ENGINE_EVENTS_RECEIVER_FORWARDER_GUARD
