# include_directories(${PROJECT_SOURCE_DIR}/include)
add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors -O3)
add_executable(aoc main.cpp)