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

#ifndef ENGINE_EVENTS_BROADCASTER_GUARD
#define ENGINE_EVENTS_BROADCASTER_GUARD

#include <memory>
#include <algorithm>
#include <queue>
#include <functional>
#include <mutex>
#include <set>

#include "engine/events/interfaces/Node.h"

namespace engine
{
    namespace events
    {
        template < typename Event_type >
            class Broadcaster : public Node < Event_type >
            {
                public:
                    Broadcaster ();
                    virtual void subscribe ( std::shared_ptr < Receiver < Event_type > > subscriber );
                    virtual void unsubscribe ( Receiver < Event_type >* unsubscriber );
                    virtual void receive ( Event_type event );

                    virtual ~Broadcaster () noexcept = default;

                private:
                    void empty_queues ();

                    std::set < std::shared_ptr < Receiver < Event_type > > > subscribers;

                    // To see why these are neccessary, take a look at the corresponding tests
                    // at tests/engine/events/Broadcaster.cpp
                    std::queue < Receiver < Event_type >* > unsubscriber_queue;
                    std::queue < std::shared_ptr < Receiver < Event_type > > > subscriber_queue;

                    bool subscribers_lock;

                    std::mutex unsubscribe_mutex;
            };


        template < typename Event_type >
            Broadcaster < Event_type >::Broadcaster () :
                subscribers_lock ( false )
            {}

        template < typename Event_type >
            void Broadcaster < Event_type >::subscribe ( std::shared_ptr < Receiver < Event_type > > subscriber )
            {
                if ( !subscribers_lock )
                    subscribers.insert ( subscriber );
                else
                    subscriber_queue.push ( subscriber );
            }

        template < typename Event_type >
            void Broadcaster < Event_type >::unsubscribe ( Receiver < Event_type >* unsubscriber )
            {
                if ( !subscribers_lock )
                {
                    std::unique_lock < std::mutex > unsubscribe_lock ( unsubscribe_mutex );

                    // Lambda method to search for unsubscriber in subscribers
                    auto is_unsubscriber = [] ( std::shared_ptr < Receiver < Event_type > > it, Receiver < Event_type >* unsubscriber )
                        { return it.get () == unsubscriber; };

                    auto unsubscriber_iterator = std::find_if ( subscribers.begin (), subscribers.end (),
                        std::bind ( is_unsubscriber, std::placeholders::_1, unsubscriber ) );

                    if ( unsubscriber_iterator != subscribers.end () )
                        subscribers.erase ( unsubscriber_iterator );
                }
                else
                    unsubscriber_queue.push ( unsubscriber );
            }

        template < typename Event_type >
            void Broadcaster < Event_type >::receive ( Event_type event )
            {
                subscribers_lock = true;
                for ( auto receiver : subscribers )
                    receiver->receive ( event );

                subscribers_lock = false;
                empty_queues ();
            }

        template < typename Event_type >
            void Broadcaster < Event_type >::empty_queues ()
            {
                while ( !unsubscriber_queue.empty () )
                {
                    unsubscribe ( unsubscriber_queue.front () );
                    unsubscriber_queue.pop ();
                }

                while ( !subscriber_queue.empty () )
                {
                    subscribe ( subscriber_queue.front () );
                    subscriber_queue.pop ();
                }
            }

    } /* namespace events */
} /* namespace engine */

#endif // ENGINE_EVENTS_BROADCASTER_GUARD
