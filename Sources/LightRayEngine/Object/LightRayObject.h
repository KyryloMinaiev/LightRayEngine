//
// Created by MrFlyingChip on 12.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LIGHTRAYOBJECT_H
#define LIGHTRAYAPPLICATION_LIGHTRAYOBJECT_H

#include "JsonLibrary.h"
#include <vector>

namespace LightRayEngine {
    class LightRayObject : public JsonLibrary::JsonSerialized {
    public:
        explicit LightRayObject(int objectID);
        ~LightRayObject() override = default;

        [[nodiscard]] int GetID() const;

        void FromJson(JsonLibrary::JsonObject &jsonObject) override {
            name = jsonObject["name"].operator std::string();
        };

        void ToJson(JsonLibrary::JsonObject &jsonObject) const override {
            jsonObject["name"] = name;
        };

        std::string name;

    private:
        int m_objectID;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LIGHTRAYOBJECT_H
