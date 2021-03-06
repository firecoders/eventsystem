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

#ifndef ENGINE_EVENTS_BLOCKING_FORWARDER_GUARD
#define ENGINE_EVENTS_BLOCKING_FORWARDER_GUARD

#include <mutex>

#include "interfaces/Forwarder.h"
#include "Receiver_forwarder.hpp"

namespace engine
{
    namespace events
    {
        template < typename Event_type >
            class Blocking_forwarder : public Forwarder < Event_type >
            {
                public:
                    Blocking_forwarder ( std::shared_ptr < Receiver < Event_type > > target );

                    virtual void receive ( Event_type event );
                    void redirect ( std::shared_ptr < Receiver < Event_type > > target );

                    virtual ~Blocking_forwarder () noexcept = default;

                private:
                    std::mutex unique_mutex;
                    Receiver_forwarder < Event_type > receiver_forwarder;
            };

        template < typename Event_type >
            Blocking_forwarder < Event_type >::Blocking_forwarder ( std::shared_ptr < Receiver < Event_type > > target ) :
                receiver_forwarder ( target )
            {}

        template < typename Event_type >
            void Blocking_forwarder < Event_type >::receive ( Event_type event )
            {
                std::unique_lock < std::mutex > lock ( unique_mutex );
                receiver_forwarder.receive ( event );
            }

        template < typename Event_type >
            void Blocking_forwarder < Event_type >::redirect ( std::shared_ptr < Receiver < Event_type > > target )
            {
                receiver_forwarder.redirect ( target );
            }
    } /* namespace events */
} /* namespace engine */

#endif // ENGINE_EVENTS_BLOCKING_FORWARDER_GUARD
