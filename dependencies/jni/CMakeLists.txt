# add include to jni hook
target_include_directories(jnihook PUBLIC
        include
)

target_link_directories(jnihook PUBLIC
        lib
)