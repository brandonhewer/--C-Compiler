find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(CParser src/C.y ${CMAKE_CURRENT_BINARY_DIR}/C.tab.c 
             COMPILE_FLAGS "-v -t --defines=inc/Parser/C.tab.h")
FLEX_TARGET(CScanner src/C.flex ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
ADD_FLEX_BISON_DEPENDENCY(CScanner CParser)

add_library(DecrementCParser
  src/ASTNode.cpp
  src/SymbolTable.cpp
  ${BISON_CParser_OUTPUTS}
  ${FLEX_CScanner_OUTPUTS}
)

target_include_directories(DecrementCParser PUBLIC inc)
