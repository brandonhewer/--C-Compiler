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

add_test(NAME ANormalFormTest COMMAND ANormalFormTest)
