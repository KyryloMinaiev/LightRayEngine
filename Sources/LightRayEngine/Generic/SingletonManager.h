//
// Created by Kirill Minaev on 18.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_SINGLETONMANAGER_H
#define LIGHTRAYAPPLICATION_SINGLETONMANAGER_H

namespace LightRayEngine{
    #define DECLARE_SINGLETON(Type) Type* SingletonManager<Type>::s_instance;

    template <class T>
    class SingletonManager{
    public:
        SingletonManager() {
            s_instance = (T*)this;
        };
        virtual ~SingletonManager() = default;
    protected:
        static T* s_instance;
    };

    template <class T>
    T* SingletonManager<T>::s_instance;
}

#endif //LIGHTRAYAPPLICATION_SINGLETONMANAGER_H
