#pragma once
#include <typeinfo>
#include <functional>
#include <map>

#include "../EditorWindowManager.h"
#include "ConsoleWindow.h"
#include "Hierarchy.h"
#include "InspectorWindow.h"
#include "ProjectView.h"
#include "SceneView.h"

namespace LightRayEngine {
    std::map<std::string, std::function<EditorWindow *(std::string)>> availableWindows =
    {
        {typeid(ConsoleWindow).name(),   EditorWindowManager::CreateBasicEditorWindow<ConsoleWindow>},
        {typeid(Hierarchy).name(),       EditorWindowManager::CreateBasicEditorWindow<Hierarchy>},
        {typeid(InspectorWindow).name(), EditorWindowManager::CreateBasicEditorWindow<InspectorWindow>},
        {typeid(ProjectView).name(),     EditorWindowManager::CreateBasicEditorWindow<ProjectView>},
        {typeid(SceneView).name(),       EditorWindowManager::CreateBasicEditorWindow<SceneView>},
    };
}
