
# All files in the source-dir included in build!
file(GLOB ETK_SRC src/*.cpp )

add_library(etk ${ETK_SRC} )

# target_link_libraries(etk PUBLIC wxWidgets::wxWidgets )

target_include_directories( etk PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

pzen_validate(etk)
