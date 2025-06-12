//
// Created by MrFlyingChip on 21.08.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTCREATINGWINDOW_H
#define LIGHTRAYENGINE_PROJECTCREATINGWINDOW_H

#include "../EditorWindow.h"
#include <functional>
#include <string>
#include "Generic/Delegates/Action.h"

namespace LightRayEngine
{
    using ProjectCreationCallbackAction = Action<const std::string &, const std::string &>;
    using ProjectPathCheckCallback = Delegate<bool(const std::string &)>;

    class ProjectCreatingWindow : public EditorWindow
    {
        public:
            explicit ProjectCreatingWindow(EditorWindowManager *editorWindowManager);
            static ProjectCreatingWindow* Create(const ProjectCreationCallbackAction &projectCreationCallback,
                               const ProjectPathCheckCallback &projectPathCheckCallback);
            void OnGui() override;
        private:
            bool IsNameValid();
            bool IsPathValid();

            std::string m_projectName;
            std::string m_projectPath;
            ProjectCreationCallbackAction m_projectCreationCallback;
            ProjectPathCheckCallback m_projectPathCheckCallback;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTCREATINGWINDOW_H
