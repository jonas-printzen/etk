#include <gtest/gtest.h>

#include <etk/types.hpp>
using namespace etk;

TEST(Types,Assumptions) {
  // Generic assumptions
  EXPECT_EQ( 4, sizeof(int)  );
  EXPECT_EQ( 8, sizeof(long)  );
  EXPECT_EQ( 4, sizeof(float)  );
  EXPECT_EQ( 8, sizeof(double)  );

  EXPECT_EQ( 4, sizeof(hash32_t)  );
  EXPECT_EQ( 8, sizeof(hash64_t)  );

  EXPECT_EQ( 1211972381U, H32("pzen.net") );
  EXPECT_EQ( 16352408660794792637UL, H64("pzen.net") );
}

using ADummy = APod<0>;
using AInt = APod<H32("int"),int>;
using ALong = APod<H32("long"),long>;

// Generic assumptions
TEST(POD,Assumptions) {
  EXPECT_EQ( 4, sizeof(int)  );
  EXPECT_EQ( 8, sizeof(long)  );

  ADummy dum;
  AInt i{17};
  ALong l{42};

  EXPECT_EQ( 17, *i );

  // To hit the const
  const ALong &cl = l;
  EXPECT_EQ( 42, *cl );

  EXPECT_EQ( 4, sizeof(dum.type)  );
  EXPECT_EQ( 4, AInt::LEN );
  EXPECT_EQ( 4, i.payload().size() );
  EXPECT_EQ( 12, AInt::SIZE );
  EXPECT_EQ( 12, i.all().size()  );
  EXPECT_EQ( 8, ALong::LEN  );
  EXPECT_EQ( 16, ALong::SIZE  );
  EXPECT_EQ( 16, l.all().size()  );
}

struct TestRec {
  int x,y,w,h;
};

using ARec = APod<H32("TestRec"),TestRec>;

TEST( POD, Struct ) {
  ARec rec{1,2,3,4};

  EXPECT_EQ( ARec::TYPE, rec.type );
  EXPECT_EQ( ARec::LEN, rec.len );

  auto payload = rec.payload();

  EXPECT_EQ( 4*4, payload.size() );

  EXPECT_EQ( 1, rec->x );
  EXPECT_EQ( 2, rec->y );

  // To it const...
  const ARec &crec = rec;
  EXPECT_EQ( 3, crec->w );
  EXPECT_EQ( 4, crec->h );
  
}

