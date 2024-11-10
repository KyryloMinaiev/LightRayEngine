//
// Created by Kirill Minaev on 10.07.2024.
//

#ifndef LIGHTRAYENGINE_EDITORLOOPSYSTEM_H
#define LIGHTRAYENGINE_EDITORLOOPSYSTEM_H

#include "../EditorConfigurationSettings/EditorConfigurationSettings.h"

namespace LightRayEngine {
    class EditorLoopSystem {
        public:
            EditorLoopSystem(EditorConfigurationSettings* editorSettings){
                configurationSettings = editorSettings;
            }

            virtual void OnLoopStop() {}

            virtual ~EditorLoopSystem() = default;
        protected:
            EditorConfigurationSettings* configurationSettings;
    };
}

#endif //LIGHTRAYENGINE_EDITORLOOPSYSTEM_H
