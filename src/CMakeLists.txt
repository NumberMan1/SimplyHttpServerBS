cmake_minimum_required(VERSION 3.2)

file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR}/src "*.cpp" "*.cc")

add_library(mysrc STATIC ${src})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mysrc PUBLIC Threads::Threads)

if(MSVC)
    target_compile_options(mysrc PRIVATE /W4 /WX)
else()
    target_compile_options(mysrc PRIVATE -Wall -Wextra -pedantic -Werror)
endif()