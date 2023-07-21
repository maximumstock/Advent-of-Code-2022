# include_directories(${PROJECT_SOURCE_DIR}/include)
add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors -O3)
add_executable(aoc main.cpp)
target_link_libraries(aoc PRIVATE dbg_macro)