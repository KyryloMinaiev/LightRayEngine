//
// Created by MrFlyingChip on 27.07.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H
#define LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H

#include "../EditorWindow.h"

namespace LightRayEngine {
    class ProjectWizardWindow : public EditorWindow {
    public:
        void OnCreate() override;
        void OnGui() override;
        static void Create();
    private:
        void LoadLastProjects();
    };
}


#endif //LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H
