cmake_minimum_required(VERSION 3.31)
project(OpenGL_Restart)

set(CMAKE_CXX_STANDARD 20)

# Recursively collect only .cpp and .hpp files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS include/*.hpp)

add_executable(OpenGL_Restart ${SOURCE_FILES} ${HEADER_FILES})

# === GLFW ===
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/GLFW/include")
set(GLFW_LIB_DIR     "${CMAKE_SOURCE_DIR}/thirdparty/GLFW/lib")
set(GLFW_DLL_PATH    "${CMAKE_SOURCE_DIR}/thirdparty/GLFW/bin/glfw3.dll")

# === GLAD ===
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/glad/include")
set(GLAD_LIB_DIR     "${CMAKE_SOURCE_DIR}/thirdparty/glad/lib")
set(GLAD_DLL_PATH    "${CMAKE_SOURCE_DIR}/thirdparty/glad/bin/glad.dll")

# Include directories
target_include_directories(OpenGL_Restart
        PRIVATE
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# Link directories
target_link_directories(OpenGL_Restart
        PRIVATE
        ${GLFW_LIB_DIR}
        ${GLAD_LIB_DIR}
)

# Link libraries (MinGW)
target_link_libraries(OpenGL_Restart
        PRIVATE
        glfw3dll
        glad
        opengl32
)

# Copy DLLs post-build
add_custom_command(TARGET OpenGL_Restart POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_DLL_PATH}"
        "${GLAD_DLL_PATH}"
        $<TARGET_FILE_DIR:OpenGL_Restart>
)

# Copy shader files to build directory
add_custom_command(TARGET OpenGL_Restart POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:OpenGL_Restart>/shaders"
)
