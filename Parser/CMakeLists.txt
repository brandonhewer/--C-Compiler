add_library(--CParser INTERFACE)

target_include_directories(--CParser
  INTERFACE
    inc
    ${Boost_INCLUDE_DIRS}
)

add_subdirectory(test)

target_link_libraries(--CParser
  INTERFACE
    ${Boost_LIBRARIES}
)
