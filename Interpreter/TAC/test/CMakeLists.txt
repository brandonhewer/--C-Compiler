add_executable(Minus2CTACTest
  src/main.cpp
  src/TACTest.cpp
)

target_include_directories(Minus2CTACTest PRIVATE inc)

target_link_libraries(Minus2CTACTest
  PUBLIC
    Minus2CTAC
    gtest_main
)

target_compile_definitions(Minus2CTACTest 
  PRIVATE TEST_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test-data")

add_test(NAME Minus2CTACTest COMMAND Minus2CTACTest)