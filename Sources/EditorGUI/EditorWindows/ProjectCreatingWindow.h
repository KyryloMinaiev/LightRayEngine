//
// Created by MrFlyingChip on 21.08.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTCREATINGWINDOW_H
#define LIGHTRAYENGINE_PROJECTCREATINGWINDOW_H

#include "../EditorWindow.h"
#include <functional>
#include <string>

#define ProjectCreationCallback std::function<void(std::string, std::string)>

namespace LightRayEngine {
    class ProjectCreatingWindow : public EditorWindow {
    public:
        static void Create(ProjectCreationCallback projectCreationCallback);
        void OnGui() override;
    private:
        bool IsNameValid();
        bool IsPathValid();

        ProjectCreationCallback m_projectCreationCallback;
        std::string m_projectName;
        std::string m_projectPath;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTCREATINGWINDOW_H
