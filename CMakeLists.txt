cmake_minimum_required(VERSION 3.5)

# compiler to gcc
set(CMAKE_C_COMPILER gcc)

project(fractal_gen)

include_directories(include)

# get all c files from src
file(GLOB SRC_FILES src/*.c)

add_executable(fractal_gen ${SRC_FILES})

#link agenst libm the math library
target_link_libraries(fractal_gen m)

# save executable to main directory
set_target_properties(fractal_gen PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# debug options
# target_compile_options(fractal_gen PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
# target_link_libraries(fractal_gen PRIVATE m -fsanitize=address)
set(CMAKE_BUILD_TYPE Debug)