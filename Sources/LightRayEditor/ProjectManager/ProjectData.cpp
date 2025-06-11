//
// Created by MrFlyingChip on 09.06.2025.
//

#include "ProjectData.h"

namespace LightRayEngine
{
    void ProjectData::FromJson(JsonLibrary::JsonObject &jsonObject)
    {
        name = static_cast<std::string>(jsonObject["name"]);
        path = static_cast<std::string>(jsonObject["path"]);
        isFavourite = jsonObject["isFavourite"];
        jsonObject["changeTime"].DecodeObject(changeTime);
    }

    void ProjectData::ToJson(JsonLibrary::JsonObject &jsonObject)
    {
        jsonObject["name"] = name;
        jsonObject["path"] = path;
        jsonObject["isFavourite"] = isFavourite;
        jsonObject["changeTime"].EncodeObject(changeTime);
    }

    ProjectData::ProjectData(const std::string &name, const std::string &path, const SerializedTime &changeTime,
                             bool isFavourite) : name(name), path(path), changeTime(changeTime),
                                                 isFavourite(isFavourite)
    {}

    ProjectData::ProjectData(const std::string &name, const std::string &path, const SerializedTime &changeTime) : name(
            name), path(path), changeTime(changeTime),
                                                                                                                   isFavourite(
                                                                                                                           false)
    {

    }

    ProjectData::ProjectData() = default;
} // LightRayEngine