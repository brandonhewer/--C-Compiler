#ifndef _EXPRESSION_TEST_HPP
#define _EXPRESSION_TEST_HPP

#include "gtest/gtest.h"

class ExpressionTest : public ::testing::Test {
protected:
  ExpressionTest();

  virtual ~ExpressionTest();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
