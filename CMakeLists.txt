cmake_minimum_required(VERSION 3.27)
project(minecraft_mod_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

if (NOT WIN32)
    # this only works for win32, it relies on windows specific APIs
    message(FATAL_ERROR "This library only works on windows")
endif ()

add_library(${PROJECT_NAME} SHARED
        dll_entry.cpp
)

# sources
add_subdirectory(jni)
add_subdirectory(minecraft_sdk)
add_subdirectory(srcs)

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

target_link_libraries(${PROJECT_NAME} PRIVATE
        custom_lib
        jnihook
        minhook
)

