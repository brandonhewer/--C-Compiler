#ifndef PARSERTEST_H
#define PARSERTEST_H

#include "gtest/gtest.h"

class ParserTest : public ::testing::Test {
protected:
  ParserTest();

  virtual ~ParserTest();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
