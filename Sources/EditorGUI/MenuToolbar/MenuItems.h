//
// Created by MrFlyingChip on 14.07.2024.
//

#ifndef LIGHTRAYENGINE_MENUITEMS_H
#define LIGHTRAYENGINE_MENUITEMS_H

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace LightRayEngine {
    struct MenuItem {
        std::string path;
        std::function<void()> callback;

        MenuItem(std::string path, const std::function<void()> &callback) {
            this->path = std::move(path);
            this->callback = callback;
        }
    };

    std::vector<MenuItem> menuItems =
    {
        MenuItem("File/Save Project", nullptr),
        MenuItem("Windows/Inspector", nullptr),
        MenuItem("Windows/Console", nullptr),
        MenuItem("Windows/Scene View", nullptr),
        MenuItem("Windows/Hierarchy", nullptr),
        MenuItem("Windows/Project", nullptr)
    };
}

#endif //LIGHTRAYENGINE_MENUITEMS_H
