set(third_party_folder "ThirdParty")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if(NOT TARGET glad)
    add_subdirectory(glad)
    set_target_properties(glad PROPERTIES FOLDER ${third_party_folder}/glad)
endif()

if(NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
endif()

if(NOT TARGET glm)
    add_subdirectory(glm)
    set_target_properties(glm PROPERTIES FOLDER ${third_party_folder}/glm)
endif()

if(NOT TARGET stb)
    add_subdirectory(stb)
    set_target_properties(stb PROPERTIES FOLDER ${third_party_folder}/stb)
endif()

if(NOT TARGET yaml-cpp)
    add_subdirectory(yaml-cpp)
    set_target_properties(yaml-cpp PROPERTIES FOLDER ${third_party_folder}/yaml_cpp)
endif()