//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTNAMEWINDOW_H
#define LIGHTRAYAPPLICATION_LAYOUTNAMEWINDOW_H

#include "EditorGUI/EditorWindow.h"
#include <functional>

namespace LightRayEngine {
    class LayoutNameWindow : public EditorWindow {
    public:
        ~LayoutNameWindow() override;

        static void Create(const std::function<void(const std::string&)>& onCreateButtonClick);

        void OnGui() override;

    private:
        std::string m_inputName;
        std::function<void(const std::string&)> m_onCreateButtonClick;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTNAMEWINDOW_H
