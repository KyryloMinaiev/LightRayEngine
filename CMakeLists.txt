cmake_minimum_required(VERSION 3.28)
project(LightRayEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(LightRayEngine Sources/main.cpp)

file(GLOB_RECURSE CORE_SOURCES
        Sources/Core/*.cpp
)

file(GLOB_RECURSE GUI_SOURCES
        Sources/EditorGUI/*.cpp
)

target_sources(LightRayEngine
        PRIVATE
        ${CORE_SOURCES}
        ${GUI_SOURCES}
)

target_include_directories(LightRayEngine
        PRIVATE
        Sources/Core
        Sources/EditorGUI
)

IF (WIN32)
    target_include_directories(LightRayEngine PRIVATE Sources/ExternalTools/GLEW/include
            Sources/ExternalTools/GLFW/include
            Sources/ExternalTools/glm
            Sources/ExternalTools/stb)

    target_link_directories(LightRayEngine PRIVATE Sources/ExternalTools/GLFW
            Sources/ExternalTools/GLEW)

    find_library(GLEW_PATH glew32.lib PATHS Sources/ExternalTools/GLEW/lib/)
    find_library(GLTW_PATH glfw3.lib PATHS Sources/ExternalTools/GLFW/lib/)
    find_library(OPENGL_PATH opengl32.lib PATHS Sources/ExternalTools/OpenGL/lib/)

    configure_file(Sources/ExternalTools/GLEW/dll/glew32.dll ${CMAKE_BINARY_DIR}/glew32.dll COPYONLY)
    configure_file(Sources/ExternalTools/GLFW/dll/glfw3.dll ${CMAKE_BINARY_DIR}/glfw3.dll COPYONLY)
ENDIF (WIN32)

IF (APPLE)
    target_include_directories(LightRayEngine PRIVATE Sources/ExternalTools/glm
            Sources/ExternalTools/stb
            Sources/ExternalTools/glm)

    FIND_PACKAGE(GLEW REQUIRED)
    link_directories(${GLEW_LIBRARY_DIRS})
    include_directories(${GLEW_INCLUDE_DIR})

    FIND_PACKAGE(GLFW3 REQUIRED)
    link_directories(${GLFW3_LIBRARY_DIR})
    include_directories(${GLFW3_INCLUDE_DIR})

    set(GLEW_PATH GLEW::glew)
    set(GLTW_PATH glfw)
    set(OPENGL_PATH "")
ENDIF (APPLE)

add_subdirectory(Sources/Utils)
add_subdirectory(Sources/LightRayLog)
add_subdirectory(Sources/ImGUI)
add_subdirectory(Sources/JsonLibrary)
add_subdirectory(Sources/NFD)

target_link_libraries(LightRayEngine PRIVATE imgui ${OPENGL_PATH} ${GLEW_PATH} ${GLTW_PATH}
        light-ray-utils
        light-ray-log
        json-library
        native-file-dialog)