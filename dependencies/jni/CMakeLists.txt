# jdk version found here
# https://developer.ibm.com/languages/java/semeru-runtimes/downloads
# 17.0.9.0 OpenJDK 17.0.9+9 OpenJ9 0.41.0

# add include to jni hook
target_include_directories(jnihook PUBLIC
        include
)

target_link_directories(jnihook PUBLIC
        lib
)