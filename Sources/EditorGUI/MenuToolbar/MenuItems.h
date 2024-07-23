#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "../EditorWindows/ConsoleWindow.h"
#include "../EditorWindows/Hierarchy.h"
#include "../EditorWindows/InspectorWindow.h"
#include "../EditorWindows/ProjectView.h"
#include "../EditorWindows/SceneView.h"

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
        MenuItem("Windows/Inspector", InspectorWindow::Create),
        MenuItem("Windows/Console", ConsoleWindow::Create),
        MenuItem("Windows/Scene View", SceneView::Create),
        MenuItem("Windows/Hierarchy", Hierarchy::Create),
        MenuItem("Windows/Project", ProjectView::Create)
    };
}
