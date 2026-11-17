cmake_minimum_required(VERSION 3.20)

project(rendererWorkshop)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

add_subdirectory(external/glm)

add_library(glad
	external/glad/src/gl.c
)

target_include_directories(glad SYSTEM PUBLIC
	include
	external/glad/include
)

add_executable(rendererWorkshop
	main.cpp
	src/Shader.cpp
	src/Texture.cpp
	src/stb_image.cpp
)

target_include_directories(rendererWorkshop PRIVATE
	external/stb
)

target_link_libraries(rendererWorkshop PRIVATE
	glfw
	glad
	glm::glm
)

target_compile_definitions(rendererWorkshop PRIVATE GLFW_INCLUDE_NONE)

add_custom_command(TARGET rendererWorkshop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:rendererWorkshop>/shaders
)
add_custom_command(TARGET rendererWorkshop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:rendererWorkshop>/textures
)
