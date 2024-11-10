file(GLOB_RECURSE ENGINE_SOURCES
        *.cpp
)

add_library(LightRayEngine STATIC LightRayEngine.cpp)
target_sources(LightRayEngine PUBLIC ${ENGINE_SOURCES})

target_include_directories(LightRayEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../glm)

add_subdirectory(../Utils ${CMAKE_BINARY_DIR}/Utils)
add_subdirectory(../LightRayLog ${CMAKE_BINARY_DIR}/LightRayLog)
add_subdirectory(../JsonLibrary ${CMAKE_BINARY_DIR}/JsonLibrary)
add_subdirectory(../NFD ${CMAKE_BINARY_DIR}/NFD)
add_subdirectory(../glm ${CMAKE_BINARY_DIR}/glm)
add_subdirectory(../ImGUI ${CMAKE_BINARY_DIR}/ImGUI)

target_link_libraries(LightRayEngine PUBLIC
        imgui
        light-ray-utils
        light-ray-log
        json-library
        native-file-dialog
        glm)