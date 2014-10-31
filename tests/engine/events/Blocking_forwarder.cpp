/* 2D-engine, A generic C++ eventsystem library utilizing templates
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

#include <mutex>
#include <memory>
#include <string>

#include <chrono>
#include <thread>
#include <regex>

#include "engine/events/interfaces/Receiver.h"
#include "engine/events/Blocking_forwarder.hpp"
#include "engine/events/Detaching_forwarder.hpp"

using namespace engine::events;

template < typename Event_type >
    class Test_receiver_block : public Receiver < Event_type >
    {
        public:
        Test_receiver_block ()
            {
                join_mutex.lock ();
            }

            virtual void receive ( Event_type e )
            {
                for ( int i = 0; i < 10; i++ ){
                    result.append ( e );
                }

                if( result.length() >= 20)
                {
                    join_mutex.unlock ();
                }
            }

            virtual void join ()
            {
                join_mutex.lock ();
            }

            std::mutex join_mutex;
            std::string result;
    };

TEST ( engineEventsBlockingForwarder, generalTest )
{
    std::shared_ptr < Test_receiver_block < std::string > > test_receiver = std::make_shared < Test_receiver_block < std::string > > ();
    std::shared_ptr < Blocking_forwarder < std::string > > test_blocking_forwarder = std::make_shared < Blocking_forwarder < std::string > > (test_receiver);
    Detaching_forwarder < std::string > test_detaching_forwarder ( test_blocking_forwarder );

    test_detaching_forwarder.receive ( "a" );
    test_detaching_forwarder.receive ( "b" );

    test_receiver->join ();

    std::string expected_result = (test_receiver->result[0] == 'a' )? "aaaaaaaaaabbbbbbbbbb" : "bbbbbbbbbbaaaaaaaaaa";
    EXPECT_EQ ( expected_result, test_receiver->result );
}
