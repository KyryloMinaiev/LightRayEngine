add_library(imgui STATIC
        imgui.h
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_truetype.h
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_glfw.h
        backends/imgui_impl_opengl3.cpp
        backends/imgui_impl_opengl3.h
        backends/imgui_impl_opengl3_loader.h
        misc/cpp/imgui_stdlib.cpp)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ../../ExternalLibraries/GLFW/include)

target_link_libraries(imgui PUBLIC ${GLTW_PATH})