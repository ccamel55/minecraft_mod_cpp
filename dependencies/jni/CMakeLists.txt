# jdk version found here
# https://adoptium.net/temurin/releases/?version=17&os=windows&arch=x64&package=jdk
# jdk-17.0.9+9.1

# add include to jni hook
target_include_directories(jnihook PUBLIC
        include
)

target_link_directories(jnihook PUBLIC
        lib
)