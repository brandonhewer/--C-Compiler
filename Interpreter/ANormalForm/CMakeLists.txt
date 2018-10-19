
add_library(Minus2CANormalForm
  src/Expression.cpp
  src/Printers.cpp
)

target_include_directories(Minus2CANormalForm
  PUBLIC
    inc
)

target_link_libraries(Minus2CANormalForm
  PUBLIC
    Minus2CParser
)

add_subdirectory(test)
