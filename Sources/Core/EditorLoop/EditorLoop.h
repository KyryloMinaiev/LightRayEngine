//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORLOOP_H
#define LIGHTRAYENGINE_EDITORLOOP_H

#include "../EditorConfigurationSettings.h"

class EditorLoop {
    public:
        EditorLoop(const EditorConfigurationSettings& editorConfiguration);
        ~EditorLoop();

        void Update();
};


#endif //LIGHTRAYENGINE_EDITORLOOP_H
