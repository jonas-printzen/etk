#include <gtest/gtest.h>

#include <etk/ring.hpp>
using namespace etk;

using TQueue = RingBuff<2>;

TEST(Ring,Assumptions) {
  // Generic assumptions
  EXPECT_EQ( 32, sizeof(TQueue::payload_t) );

  TQueue q;
  EXPECT_EQ( false, q.full() );
  EXPECT_EQ( true, q.empty() );
  EXPECT_EQ( 0U, q.count() );
  EXPECT_EQ( nullptr, q.head<int>() );

  EXPECT_EQ( true, q.push(42) );
  EXPECT_EQ( false, q.full() );
  EXPECT_EQ( false, q.empty() );
  EXPECT_EQ( 1U, q.count() );
  EXPECT_NE( nullptr, q.head<int>() );

  EXPECT_EQ( true, q.push(17) );
  EXPECT_EQ( 2U, q.count() );

  EXPECT_EQ( false, q.push(37) );
  EXPECT_EQ( 2U, q.count() );

  EXPECT_EQ( 42, *q.head<int>() );
  EXPECT_EQ( true, q.pop() );
  EXPECT_EQ( 1U, q.count() );

  int out=0;

  EXPECT_EQ( true, q.pop(out) );
  EXPECT_EQ( 17, out );
  EXPECT_EQ( 0U, q.count() );

  out = 1;
  EXPECT_EQ( false, q.pop(out) );
  EXPECT_EQ( 1, out );
  EXPECT_EQ( false, q.pop() );

  EXPECT_EQ( true, q.push(37) );
  EXPECT_EQ( 1U, q.count() );
  EXPECT_EQ( 37, *q.head<int>() );

  q.reset();
  EXPECT_EQ( 0U, q.count() );
  EXPECT_EQ( nullptr, q.head<int>() );
  
}
