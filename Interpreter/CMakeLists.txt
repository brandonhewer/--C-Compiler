add_subdirectory(ANormalForm)

add_custom_target(
  --CInterpreter
    DEPENDS
      ANormalForm
)

add_custom_target(
  --CInterpreterTests
    DEPENDS
      ANormalFormTest
)
