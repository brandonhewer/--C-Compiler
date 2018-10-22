add_library(Minus2CTAC
  src/ANormalFormToTAC.cpp
  src/AssignmentToTAC.cpp
  src/Closure.cpp
  src/Environment.cpp
  src/Frame.cpp
  src/PrintTAC.cpp
)

target_include_directories(Minus2CTAC
  PUBLIC
    inc
)

target_link_libraries(Minus2CTAC
  PUBLIC
    Minus2CANormalForm
)

add_subdirectory(test)
