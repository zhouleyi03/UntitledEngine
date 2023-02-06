project(stb)
# trick ?
add_library(stb stb_vorbis.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})