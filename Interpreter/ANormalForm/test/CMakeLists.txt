add_executable(ANormalFormTest
  src/main.cpp
  src/ExpressionTest.cpp
)

target_include_directories(ANormalFormTest PRIVATE inc)

target_link_libraries(ANormalFormTest
  PUBLIC
    ANormalForm
    gtest_main
)

target_compile_definitions(ANormalFormTest 
  PRIVATE TEST_PATH="${CMAKE_SOURCE_DIR}/test-data")

add_test(NAME ANormalFormTest COMMAND ANormalFormTest)
