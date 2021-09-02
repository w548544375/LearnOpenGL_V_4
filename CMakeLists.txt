cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenGL_GL_PREFERENCE "GLVND")

add_subdirectory(lib/gl3w)
add_subdirectory(lib/glm)

add_executable(${PROJECT_NAME} 
lib/gl3w/src/gl3w.c
source/Scene.cpp
source/TrangleScene.cpp 
source/ShaderLoader.cpp 
source/TextureScene.cpp
source/Scene3D.cpp
source/Object3D.cpp
source/Camera3D.cpp
source/SimpleLightScene.cpp
source/StbImage.cpp 
main.cpp)

find_package(glfw3 REQUIRED)

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/lib/gl3w/include"
    "${PROJECT_SOURCE_DIR}/lib/glm"
    "${PROJECT_SOURCE_DIR}/include"
)


target_link_libraries(${PROJECT_NAME} 
    PUBLIC glfw
    PUBLIC OpenGL::OpenGL
    PUBLIC gl3w   
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})