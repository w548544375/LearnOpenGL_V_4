cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenGL_GL_PREFERENCE "GLVND")

set(ASSIMP_BUILD_TESTS "OFF")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#windows
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#linux
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(lib/gl3w external/gl3w)
add_subdirectory(lib/glm external/glm)
add_subdirectory(lib/SDL external/SDL)
add_subdirectory(lib/glfw external/glfw)
add_subdirectory(lib/assimp external/assimp)
# 遍历source文件夹的cpp文件
set(SOURCE_LIST "")
file(GLOB LEARN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
foreach(cppfile ${LEARN_SOURCES})
    list(APPEND SOURCE_LIST ${cppfile})
endforeach()

set(HEADER_LIST "")
file(GLOB LEARN_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
foreach(header ${LEARN_HEADERS})
    list(APPEND HEADER_LIST ${header})
endforeach()


add_executable(${PROJECT_NAME}
${SOURCE_LIST}
${HEADER_LIST}
main.cpp)

find_package(OpenGL REQUIRED)
if(${OPENGL_opengl_LIBRARY})
    message("Found OpenGL GLVND-based:${OPENGL_opengl_LIBRARY}")
    set(OPENGL_LIB OpenGL::OpenGL)
else()
    message("Found OpenGL: ${OPENGL_gl_LIBRARY}")
    set(OPENGL_LIB OpenGL::GL)
endif()

include_directories(
     "${PROJECT_SOURCE_DIR}/include"
     "${PROJECT_SOURCE_DIR}/lib/glfw/include"
     "${PROJECT_SOURCE_DIR}/lib/gl3w/include"
     "${PROJECT_SOURCE_DIR}/lib/glm"
     "${PROJECT_SOURCE_DIR}/lib/SDL/include"
     "${PROJECT_SOURCE_DIR}/lib/assimp/include"
     "${PROJECT_BINARY_DIR}/external/assimp/include"
    )

#target_include_directories(${PROJECT_NAME} PUBLIC
#    "${PROJECT_SOURCE_DIR}/lib/glfw/include"
#    "${PROJECT_SOURCE_DIR}/lib/gl3w/include"
#    "${PROJECT_SOURCE_DIR}/lib/glm"
#    "${PROJECT_SOURCE_DIR}/lib/SDL/include"
#    "${PROJECT_SOURCE_DIR}/include"
#)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC glfw
    PUBLIC gl3w
    PUBLIC SDL2
    PUBLIC external/SDL/SDL2maind
    PUBLIC ${OPENGL_LIB}
    PUBLIC assimp
)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
