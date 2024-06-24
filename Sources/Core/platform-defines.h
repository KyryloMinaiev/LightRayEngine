//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_PLATFORM_DEFINES_H
#define LIGHTRAYENGINE_PLATFORM_DEFINES_H

#if defined(__APPLE__)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif

#if defined(_WIN32)
    #include <glew.h>
    #include <glfw3.h>
#endif

#endif //LIGHTRAYENGINE_PLATFORM_DEFINES_H
