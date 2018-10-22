#ifndef _TAC_TEST_HPP
#define _TAC_TEST_HPP

#include "gtest/gtest.h"

class TACTest : public ::testing::Test {
protected:
  TACTest();

  virtual ~TACTest();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
