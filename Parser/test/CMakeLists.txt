add_executable(--CParserTest
  src/main.cpp
  src/ParserTest.cpp
)

target_include_directories(--CParserTest PRIVATE inc)

target_link_libraries(--CParserTest
  PUBLIC
    --CParser
    gtest_main
)

add_test(NAME --CParserTest COMMAND --CParserTest)
