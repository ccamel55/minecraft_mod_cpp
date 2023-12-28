cmake_minimum_required(VERSION 3.27)
project(minecraft_utility)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

if (NOT WIN32)
    # this only works for win32, it relies on windows specific APIs
    message(FATAL_ERROR "This library only works on windows")
endif ()

add_library(minecraft_utility SHARED
        dll_entry.cpp
)

# dependencies
set(LIB_COMMAND_PARSER off)
set(LIB_GUI on)
set(LIB_HASHING on)
set(LIB_INPUT on)
set(LIB_JSON_CONFIG on)
set(LIB_RENDERING gl3)
set(LIB_THREADING on)
set(LIB_WINDOW_CREATION off)
set(LIB_LOGGER 4)

add_subdirectory(dependencies/custom_lib)
add_subdirectory(dependencies/jnihook)
add_subdirectory(dependencies/jni)
add_subdirectory(dependencies/minhook)

target_link_libraries(minecraft_utility PRIVATE
        custom_lib
        jnihook
        minhook
)

