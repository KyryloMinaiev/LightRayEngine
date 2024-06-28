//
// Created by Kirill Minaev on 27.06.2024.
//

#ifndef LIGHTRAYENGINE_CONSOLELOGIMPL_H
#define LIGHTRAYENGINE_CONSOLELOGIMPL_H

#include <iostream>
#include <LightRayLog.h>

namespace LightRayEngine{
    class ConsoleLogImpl : public ILightRayLogUpdateSubscriber{
    public:
        ConsoleLogImpl();
        ~ConsoleLogImpl();

        void OnLogUpdated(const LogInfo &logInfo) override;

    };
}


#endif //LIGHTRAYENGINE_CONSOLELOGIMPL_H
