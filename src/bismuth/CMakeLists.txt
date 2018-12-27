file(GLOB_RECURSE SOURCES "*.c" "*.cpp")
add_executable(bismuth ${SOURCES})
target_link_libraries(bismuth libbismuth)
