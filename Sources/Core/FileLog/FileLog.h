//
// Created by Kirill Minaev on 09.07.2024.
//

#ifndef LIGHTRAYENGINE_FILELOG_H
#define LIGHTRAYENGINE_FILELOG_H

#include "LightRayLog.h"
#include "FileUtils.h"

namespace LightRayEngine {
    class FileLog : public ILightRayLogUpdateSubscriber{
    public:
        FileLog();
        virtual ~FileLog();

        void OnLogUpdated(const LogInfo &logInfo) override;

    private:
        static constexpr auto k_editorLogFileName = "editorLog.log";
    };
}


#endif //LIGHTRAYENGINE_FILELOG_H
