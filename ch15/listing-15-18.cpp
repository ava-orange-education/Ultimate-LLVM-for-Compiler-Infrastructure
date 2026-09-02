// Listing 15-18. A Google Test case from llvm/unittests

TEST(APIntTest, ZExtOrTrunc) {
  APInt Small(8, 42);
  EXPECT_EQ(Small.zextOrTrunc(16), APInt(16, 42));
}
