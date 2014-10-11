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

#include "Test_receiver.hpp"
#include "engine/events/Broadcaster.hpp"
#include "engine/events/Lambda_receiver.hpp"
#include <memory>

using namespace engine::events;

TEST ( engineEventsBroadcaster, generalTest )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();

    test_broadcaster.subscribe ( test_receiver );
    test_broadcaster.receive ( 5 );
    EXPECT_EQ ( test_receiver->result, 5 );

    test_broadcaster.unsubscribe ( test_receiver.get () );
    test_broadcaster.receive ( 6 );
    EXPECT_NE ( test_receiver->result, 6 );
    EXPECT_EQ ( test_receiver->result, 5 );
}

TEST ( engineEventsBroadcaster, unsubscribeOnReceive )
{
    Broadcaster < int > test_broadcaster;

    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto unsubscribe_on_receive = [ & ] ( int i ) { test_broadcaster.unsubscribe ( test_lambda_receiver.get () ); };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( unsubscribe_on_receive );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );
}

TEST ( engineEventsBroadcaster, subscribeOnReceive )
{
    Broadcaster < int > test_broadcaster;
    std::shared_ptr < Test_receiver < int > > test_receiver = std::make_shared < Test_receiver < int > > ();

    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    auto subscribe_on_receive = [ & ] ( int i ) { test_broadcaster.subscribe ( test_receiver ); };
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( subscribe_on_receive );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );

    test_broadcaster.receive ( 2 );
    EXPECT_EQ ( test_receiver->result, 2 );
}

TEST ( engineEventsBroadcaster, duplicateSubscription )
{
    Broadcaster < int > test_broadcaster;

    int access_count = 0;
    auto count_accesses = [ & ] ( int i ) {
        access_count ++;
    };
    std::shared_ptr < Lambda_receiver < int > > test_lambda_receiver;
    test_lambda_receiver = std::make_shared < Lambda_receiver < int > > ( count_accesses );

    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.subscribe ( test_lambda_receiver );
    test_broadcaster.receive ( 1 );
    EXPECT_EQ ( access_count, 1 );
}

