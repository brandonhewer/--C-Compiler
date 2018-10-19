add_executable(Minus2CParserTest
  src/main.cpp
  src/ParserTest.cpp
)

target_include_directories(Minus2CParserTest PRIVATE inc)

target_link_libraries(Minus2CParserTest
  PUBLIC
  Minus2CParser
    gtest_main
)

target_compile_definitions(Minus2CParserTest 
  PRIVATE TEST_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test-data")

add_test(NAME Minus2CParserTest COMMAND Minus2CParserTest)
