add_executable(Minus2CANormalFormTest
  src/main.cpp
  src/ExpressionTest.cpp
)

target_include_directories(Minus2CANormalFormTest PRIVATE inc)

target_link_libraries(Minus2CANormalFormTest
  PUBLIC
  Minus2CANormalForm
    gtest_main
)

target_compile_definitions(Minus2CANormalFormTest 
  PRIVATE TEST_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test-data")

add_test(NAME Minus2CANormalFormTest COMMAND Minus2CANormalFormTest)
