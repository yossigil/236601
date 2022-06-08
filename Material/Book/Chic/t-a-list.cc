#import  <iostream>
#import  "gtest/gtest.h"
#import  "a-list.h"
#import  "test.h"

using Engine::lookup, Engine::set;

SUITE(Lookup) 

TEST_F(Lookup, T0) {
  CAREFULLY_EXPECT(EQ,lookup("T"),"T", << 2); 
}

TEST_F(Lookup, T) {
  EXPECT_STRUE(lookup("T"));
  EXPECT_TRUE(lookup("T").eq(T));
}

TEST_F(Lookup, NIL) {
  EXPECT_SFALSE(lookup("NIL"));
  EXPECT_FALSE(lookup("NIL").t());
  EXPECT_TRUE(lookup("NIL").eq("NIL"));
  EXPECT_TRUE(lookup("NIL").null());
}

TEST_F(Lookup, Failure1) {
  EXPECT_EXCEPTION(lookup("bar baz"),S("bar baz"), UNDEFINED_ATOM);
}

TEST_F(Lookup, Failure2) {
  EXPECT_EXCEPTION(lookup("foo" "bar" "baz"), S("foo" "bar" "baz"), UNDEFINED_ATOM);
}

TEST_F(Lookup, Failure3) {
  EXPECT_EXCEPTION(lookup(" Y "), S(" Y "), UNDEFINED_ATOM);
}

TEST_F(Lookup, Failure4) {
  EXPECT_EXCEPTION(lookup("foo"), S("foo"), UNDEFINED_ATOM);
}

TEST_F(Lookup, Failure5) {
  S y("Y a b c");
  EXPECT_EXCEPTION(lookup(y), y, UNDEFINED_ATOM);
}


TEST_F(Lookup, SetGoodLookup) {
  Engine::set("X","Y");
  EXPECT_STRUE(lookup("X"));
}

TEST_F(Lookup, TeaAndCofee) {
  Engine::set("coffee","tea");
  EXPECT_EQ(lookup("coffee"), S("tea"));
  EXPECT_EXCEPTION(lookup("tea"),S("tea"), UNDEFINED_ATOM);
  Engine::set("tea","coffee");
  EXPECT_STRUE(lookup("tea"));
  EXPECT_STRUE(lookup("coffee"));
  EXPECT_EQ(lookup("tea"), S("coffee"));
}
