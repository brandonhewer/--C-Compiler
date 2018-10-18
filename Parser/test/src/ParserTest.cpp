#include "ParserTest.hpp"
#include "Parser/Parse.hpp"

#include "Parser/AST/Printers.hpp"

#include <iostream>

ParserTest::ParserTest() {}

ParserTest::~ParserTest() {}

void ParserTest::SetUp() {}

void ParserTest::TearDown() {}

TEST(ParserTest, TEST_EMPTY_MAIN_FUNCTION_IS_PARSED) {
  std::string const empty_main =
      "int a, b();int main(int a) { int a = 2 * 3 + 10 / 2; f(5); }";
  std::unordered_map<std::string, std::string> symbols;
  std::cout << "Is testing!" << std::endl;

  auto ast =
      Parser::parse_minus2c(empty_main.begin(), empty_main.end(), symbols);
  
  std::cout << "Finished tree:\n" << ast << std::endl;
}
