add_library(light-ray-log STATIC
    LightRayLog.h
    LightRayLog.cpp)
target_include_directories(light-ray-log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})