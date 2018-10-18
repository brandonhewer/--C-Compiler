
add_library(ANormalForm
  src/Expression.cpp
  src/Printers.cpp
)

target_include_directories(ANormalForm
  PUBLIC
    inc
)

target_link_libraries(ANormalForm
  PUBLIC
    --CParser
)

add_subdirectory(test)
