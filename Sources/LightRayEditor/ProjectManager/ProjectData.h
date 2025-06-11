//
// Created by MrFlyingChip on 09.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_PROJECTDATA_H
#define LIGHTRAYAPPLICATION_PROJECTDATA_H

#include <ctime>
#include "JsonLibrary.h"
#include "SerializedTime.h"

namespace LightRayEngine
{
    struct ProjectData : public JsonLibrary::JsonSerialized
    {
        std::string name;
        std::string path;
        SerializedTime changeTime;
        bool isFavourite;

        ProjectData();
        ProjectData(const std::string &name, const std::string &path, const SerializedTime &changeTime,
                    bool isFavourite);
        ProjectData(const std::string &name, const std::string &path, const SerializedTime &changeTime);

        ~ProjectData() override = default;
        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) override;
    };
} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_PROJECTDATA_H
