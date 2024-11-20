//
// Created by MrFlyingChip on 15.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_OBJECTMANAGER_H
#define LIGHTRAYAPPLICATION_OBJECTMANAGER_H

#include "LightRayObject.h"
#include "TypeManager.h"
#include <map>

namespace LightRayEngine {
    class ObjectManager {
    public:
        ObjectManager();

        ~ObjectManager();

        template<class T>
        static T *CreateObjectOfType();

        template<class T>
        static T *CreateObjectOfType(const std::string &name);

        static void DeleteObject(LightRayObject *object);

    private:
        static ObjectManager *s_instance;

        template<class T>
        T *CreateObjectOfTypeInternal(const std::string &name);

        void DeleteObjectInternal(LightRayObject *object);

        int m_idCounter{};
        std::map<int, void *> m_objectsContainer;
    };

    template<class T>
    T *ObjectManager::CreateObjectOfType() {
        const std::type_info &typeInfo = typeid(T);
        return CreateObjectOfType<T>(typeInfo.name());
    }

    template<class T>
    T *ObjectManager::CreateObjectOfType(const std::string &name) {
        return s_instance->CreateObjectOfTypeInternal<T>(name);
    }

    template<class T>
    T *ObjectManager::CreateObjectOfTypeInternal(const std::string &name) {
        static_assert(std::is_base_of<LightRayObject, T>());

        size_t typeSize = TypeManager::GetTypeSize<T>();
        void *ptr = malloc(typeSize);
        T *objectPtr = (T *) ptr;
        new(objectPtr) T(m_idCounter);
        objectPtr->name = name;
        m_objectsContainer[m_idCounter] = ptr;
        m_idCounter++;

        return objectPtr;
    }
} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_OBJECTMANAGER_H
