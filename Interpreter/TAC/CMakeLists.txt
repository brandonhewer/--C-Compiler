add_library(Minus2CTAC
  src/Environment.cpp
  src/PrintTAC.cpp
)

target_include_directories(Minus2CTAC
  PUBLIC
    inc
)

target_link_libraries(Minus2CTAC
  PUBLIC
  Minus2CParser
    ANormalForm
)

add_subdirectory(test)
