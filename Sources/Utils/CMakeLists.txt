add_library(light-ray-utils STATIC FileUtils.cpp FileUtils.h)

target_include_directories(light-ray-utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})