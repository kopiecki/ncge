set(target "ncge")
set(sources src/ll.c src/board.c src/ncge.c)

add_library(${target} STATIC ${sources})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${target} ${CURSES_LIBRARIES})

include(compiler/warnings-c)
compiler_warnings_install(${target})
