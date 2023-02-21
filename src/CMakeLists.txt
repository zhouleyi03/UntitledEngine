set(THIRD_PARTY_DIR "${UNTITLED_ENGINE_ROOT_DIR}/3rdparty")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UntitledGame)
endif()

if(WIN32)
    message(STATUS "Current Platform: Windows")
else()
    message(FATAL_ERROR "Unknown Platform!")
endif()

add_subdirectory(3rdparty)
add_subdirectory(runtime)
add_subdirectory(test)