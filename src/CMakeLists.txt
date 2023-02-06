set(TARGET_NAME UntitledGame)

file(GLOB LOGO CONFIGURE_DEPENDS logo.rc)

file(GLOB_RECURSE GAME_HEADER_FILES "*.h")
file(GLOB_RECURSE GAME_SOURCE_FILES "*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GAME_HEADER_FILES} ${GAME_SOURCE_FILES})

add_executable(${TARGET_NAME} ${GAME_HEADER_FILES} ${GAME_SOURCE_FILES} ${LOGO} main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Game")
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "Untitled")
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")
target_link_libraries(${TARGET_NAME} UntitledRuntime)