file(GLOB_RECURSE SOURCES "*.c" "*.cpp")
add_library(libbismuth STATIC ${SOURCES})
target_include_directories(libbismuth PRIVATE "${CMAKE_SOURCE_DIR}/src" PUBLIC "${CMAKE_SOURCE_DIR}/include")
set_target_properties(libbismuth PROPERTIES OUTPUT_NAME bismuth)
