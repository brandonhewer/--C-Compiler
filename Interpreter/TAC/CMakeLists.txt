add_library(--CTAC
  src/Environment.cpp
  src/PrintTAC.cpp
)

target_include_directories(--CTAC
  PUBLIC
    inc
)

target_link_libraries(--CTAC
  PUBLIC
    --CParser
    ANormalForm
)

add_subdirectory(test)
