add_library(json-library STATIC)

file(GLOB_RECURSE JSON_LIBRARY
        ./*.cpp
)

target_sources(json-library
        PRIVATE
        ${JSON_LIBRARY}
)

target_include_directories(json-library
        PRIVATE
        ./
)

target_include_directories(json-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(json-library PUBLIC light-ray-utils)