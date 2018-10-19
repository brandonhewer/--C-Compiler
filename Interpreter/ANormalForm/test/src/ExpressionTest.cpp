#include "ExpressionTest.hpp"

#include "Interpreter/ANormalForm/Printers.hpp"
#include "Interpreter/ANormalForm/TranslationUnitNormalForm.hpp"
#include "Parser/Parse.hpp"

#include <fstream>
#include <streambuf>
#include <string>

#include <ctime>

namespace {

std::string get_string_from_file_at(std::string const &full_path) {
  std::ifstream file_stream(full_path);
  if (!file_stream)
    throw std::runtime_error("No such file exists: " + full_path);
  return std::string(std::istreambuf_iterator<char>(file_stream),
                     std::istreambuf_iterator<char>());
}

std::string get_string_from_file(std::string const &file_name) {
  auto const path = std::string(TEST_PATH) + "/" + file_name;
  return get_string_from_file_at(path);
}

} // namespace

ExpressionTest::ExpressionTest() {}

ExpressionTest::~ExpressionTest() {}

void ExpressionTest::SetUp() {}

void ExpressionTest::TearDown() {}

TEST(ExpressionTest, TEST_EMPTY_MAIN_FUNCTION_IS_PARSED) {
  auto const empty_main = get_string_from_file("main.m2c");
  std::unordered_map<std::string, std::string> symbols;

  auto ast =
      Parser::parse_minus2c(empty_main.begin(), empty_main.end(), symbols);
  auto normalised = Interpreter::ANormalForm::normalise_translation_unit(ast);
  std::cout << "Finished tree:\n" << normalised << std::endl;
}
