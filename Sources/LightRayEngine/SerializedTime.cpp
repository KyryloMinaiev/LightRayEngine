//
// Created by MrFlyingChip on 21.08.2024.
//

#include "SerializedTime.h"

namespace LightRayEngine {
    void SerializedTime::FromJson(JsonLibrary::JsonObject &jsonObject) {
        tm_sec = jsonObject["sec"];
        tm_min = jsonObject["min"];
        tm_hour = jsonObject["hour"];
        tm_mday = jsonObject["mday"];
        tm_mon = jsonObject["mon"];
        tm_year = jsonObject["year"];
        tm_wday = jsonObject["wday"];
        tm_yday = jsonObject["yday"];
        tm_isdst = jsonObject["isdst"];
    }

    void SerializedTime::ToJson(JsonLibrary::JsonObject &jsonObject) const {
        jsonObject["sec"] = tm_sec;
        jsonObject["min"] = tm_min;
        jsonObject["hour"] = tm_hour;
        jsonObject["mday"] = tm_mday;
        jsonObject["mon"] = tm_mon;
        jsonObject["year"] = tm_year;
        jsonObject["wday"] = tm_wday;
        jsonObject["yday"] = tm_yday;
        jsonObject["isdst"] = tm_isdst;
    }

    SerializedTime::SerializedTime(tm &other) : tm(other) {

    }
}
