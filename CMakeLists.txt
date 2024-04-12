cmake_minimum_required (VERSION 3.14)

project(eventing_test)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wno-invalid-noreturn
                    -Wno-pragma-pack
                    -Wno-int-to-pointer-cast)

add_link_options(--no-undefined -lpthread)

set(EVENT_SOURCES
    src/main.cpp)

add_executable(eventing_test ${EVENT_SOURCES})
