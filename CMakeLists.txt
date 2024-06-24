cmake_minimum_required(VERSION 3.28)
project(LightRayEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(LightRayEngine Sources/main.cpp
        Sources/Core/EditorApplication.cpp
        Sources/Core/EditorApplication.h
        Sources/Core/platform-defines.h)

IF (WIN32)
    target_include_directories(LightRayEngine PRIVATE Sources/ExternalTools/GLEW/includes
            Sources/ExternalTools/GLFW/includes)

    find_library(GLEW_PATH glew32.lib PATHS Sources/ExternalTools/GLEW/lib/)
    message(STATUS "GLEW_PATH: " ${GLEW_PATH})

    find_library(GLTW_PATH glfw3.lib PATHS Sources/ExternalTools/GLFW/lib/)
    message(STATUS "GLTW_PATH: " ${GLTW_PATH})

    target_link_libraries(LightRayEngine ${GLEW_PATH} ${GLTW_PATH})

    configure_file(Sources/ExternalTools/GLEW/dll/glew32.dll ${CMAKE_BINARY_DIR}/glew32.dll COPYONLY)
    configure_file(Sources/ExternalTools/GLFW/dll/glfw3.dll ${CMAKE_BINARY_DIR}/glfw3.dll COPYONLY)
ENDIF (WIN32)

IF (APPLE)
    FIND_PACKAGE(GLEW REQUIRED)
    link_directories(${GLEW_LIBRARY_DIRS})
    include_directories(${GLEW_INCLUDE_DIR})

    FIND_PACKAGE(GLFW3 REQUIRED)
    link_directories(${GLFW3_LIBRARY_DIR})
    include_directories(${GLFW3_INCLUDE_DIR})

    target_link_libraries(LightRayEngine GLEW::glew glfw)
ENDIF (APPLE)
