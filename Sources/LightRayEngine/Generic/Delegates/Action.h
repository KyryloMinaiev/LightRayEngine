//
// Created by MrFlyingChip on 09.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_ACTION_H
#define LIGHTRAYAPPLICATION_ACTION_H

#include "Delegate.h"

namespace LightRayEngine {
    template<typename... Args>
    using Action = Delegate<void(Args...)>;

    template<typename T, typename ...Args>
    Action<Args...> CreateAction(T *instance, void (T::*method)(Args...))
    {
        return Action<Args...>(instance, method);
    }

    template<typename T, typename ...Args>
    Action<Args...> CreateAction(T *instance, void (T::*method)(Args...) const)
    {
        return Action<Args...>(instance, method);
    }
}

#endif //LIGHTRAYAPPLICATION_ACTION_H
