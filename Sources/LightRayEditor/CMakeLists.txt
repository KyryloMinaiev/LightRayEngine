file(GLOB_RECURSE EDITOR_SOURCES
        *.cpp
)

add_library(LightRayEditor STATIC LightRayEditor.cpp)
target_sources(LightRayEditor PUBLIC ${EDITOR_SOURCES})

target_include_directories(LightRayEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(../LightRayEngine ${CMAKE_BINARY_DIR}/LightRayEngine)

target_link_libraries(LightRayEditor LightRayEngine)