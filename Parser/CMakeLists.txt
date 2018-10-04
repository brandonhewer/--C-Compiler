if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set (BISON_EXECUTABLE "/usr/local/opt/bison/bin/bison")
endif ()

find_package(BISON 3.1 REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(CParser bison/private/C.y bison/private/C.tab.cpp 
             COMPILE_FLAGS "-v -t --defines=bison/public/Parser.hpp")
FLEX_TARGET(CScanner flex/C.flex flex/lex.yy.cpp
            COMPILE_FLAGS "--header-file=inc/Parser/Scanner.hpp")
ADD_FLEX_BISON_DEPENDENCY(CScanner CParser)

add_library(DecrementCParser
  src/ASTNode.cpp
  ${BISON_CParser_OUTPUTS}
  ${FLEX_CScanner_OUTPUTS}
)

target_include_directories(DecrementCParser PUBLIC inc bison/public)
target_include_directories(DecrementCParser PRIVATE inc bison/private)
