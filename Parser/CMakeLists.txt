add_library(Minus2CParser INTERFACE)

target_include_directories(Minus2CParser
  INTERFACE
    inc
    ${Boost_INCLUDE_DIRS}
)

add_subdirectory(test)

target_link_libraries(Minus2CParser
  INTERFACE
    ${Boost_LIBRARIES}
)
