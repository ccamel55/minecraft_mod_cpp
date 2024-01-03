target_sources(${PROJECT_NAME} PRIVATE
        instance.cpp
        menu.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        include
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
)
