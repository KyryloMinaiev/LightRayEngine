//
// Created by MrFlyingChip on 21.08.2024.
//

#ifndef LIGHTRAYENGINE_SERIALIZEDTIME_H
#define LIGHTRAYENGINE_SERIALIZEDTIME_H

#include <ctime>
#include "JsonLibrary.h"

namespace LightRayEngine {
    struct SerializedTime : public std::tm, JsonLibrary::JsonSerialized {
        ~SerializedTime() override = default;
        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) const override;
    };
}


#endif //LIGHTRAYENGINE_SERIALIZEDTIME_H
