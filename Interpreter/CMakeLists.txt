add_subdirectory(ANormalForm)
add_subdirectory(TAC)

add_custom_target(
  Minus2CInterpreter
    DEPENDS
      ANormalForm
)

add_custom_target(
  Minus2CInterpreterTest
    DEPENDS
      ANormalFormTest
)
