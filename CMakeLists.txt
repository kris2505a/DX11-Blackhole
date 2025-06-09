cmake_minimum_required(VERSION 3.31)
project(OpenGL_Restart)

set(CMAKE_CXX_STANDARD 20)

# Recursively collect .cpp and .hpp files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS include/*.hpp)

add_executable(OpenGL_Restart ${SOURCE_FILES} ${HEADER_FILES})

# === GLFW ===
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/GLFW/include")
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/GLFW/lib")  # Assume static libs here

# === GLAD ===
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/glad/include")
set(GLAD_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/glad/lib")

# Include directories
target_include_directories(OpenGL_Restart
        PRIVATE
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# Link directories (if needed)
target_link_directories(OpenGL_Restart
        PRIVATE
        ${GLFW_LIB_DIR}
        ${GLAD_LIB_DIR}
)

# Link static libraries
# On Linux, usually GLFW static lib is named libglfw3.a and GLAD static lib something like libglad.a
target_link_libraries(OpenGL_Restart
        PRIVATE
        glfw3       # static glfw3
        glad        # static glad
        dl          # dynamic loading library (needed by glad/glfw)
        pthread     # threading (needed by glfw)
        X11         # X11 system for Linux windowing
        GL          # OpenGL on Linux
)

# No DLL copying needed on Linux

# Copy shader files to build directory
add_custom_command(TARGET OpenGL_Restart POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:OpenGL_Restart>/shaders"
)
