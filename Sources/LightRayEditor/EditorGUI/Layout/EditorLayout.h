//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_EDITORLAYOUT_H
#define LIGHTRAYAPPLICATION_EDITORLAYOUT_H

#include "JsonLibrary.h"

namespace LightRayEngine {
    class EditorLayout : public JsonLibrary::JsonSerialized{
    public:
        EditorLayout();
        ~EditorLayout() override;

        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) const override;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_EDITORLAYOUT_H
