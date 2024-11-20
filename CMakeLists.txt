cmake_minimum_required(VERSION 3.28)
project(LightRayApplication)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_EDITOR "Enable LightRayEditor configuration" ON)

add_executable(LightRayApplication Sources/main.cpp)

file(GLOB_RECURSE CORE_SOURCES
        Sources/LightRayCore/*.cpp
)

target_sources(LightRayApplication
        PRIVATE
        ${CORE_SOURCES}
)

target_include_directories(LightRayApplication
        PRIVATE
        Sources/LightRayCore
)

IF (WIN32)
    target_include_directories(LightRayApplication PRIVATE ExternalLibraries/GLEW/include
            ExternalLibraries/GLFW/include
            ExternalLibraries/stb)

    target_link_directories(LightRayApplication PRIVATE ExternalLibraries/GLFW
            ExternalLibraries/GLEW)

    find_library(GLEW_PATH glew32.lib PATHS ExternalLibraries/GLEW/lib/)
    find_library(GLTW_PATH glfw3.lib PATHS ExternalLibraries/GLFW/lib/)
    find_library(OPENGL_PATH opengl32.lib PATHS ExternalLibraries/OpenGL/lib/)

    configure_file(ExternalLibraries/GLEW/dll/glew32.dll ${CMAKE_BINARY_DIR}/glew32.dll COPYONLY)
    configure_file(ExternalLibraries/GLFW/dll/glfw3.dll ${CMAKE_BINARY_DIR}/glfw3.dll COPYONLY)
ENDIF (WIN32)

IF (APPLE)
    target_include_directories(LightRayApplication PRIVATE
            ExternalLibraries/stb)

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

if(ENABLE_EDITOR)
    add_compile_definitions(LIGHTRAY_EDITOR)
    add_subdirectory(Sources/LightRayEditor)
    target_link_libraries(LightRayApplication PUBLIC ${OPENGL_PATH} ${GLEW_PATH} ${GLTW_PATH}
            LightRayEditor)
else()
    add_subdirectory(Sources/LightRayEngine)
    target_link_libraries(LightRayApplication PUBLIC ${OPENGL_PATH} ${GLEW_PATH} ${GLTW_PATH}
            LightRayEngine)
endif ()

set(RESOURCES_FOLDER ${CMAKE_SOURCE_DIR}/Resources)
set(DESTINATION_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/Resources)

add_custom_target(FullBuild ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCES_FOLDER} ${DESTINATION_FOLDER}
        COMMENT "Copying Resources folder to build directory"
)