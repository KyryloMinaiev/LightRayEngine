//
// Created by MrFlyingChip on 15.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_OBJECTMANAGER_H
#define LIGHTRAYAPPLICATION_OBJECTMANAGER_H

#include "LightRayObject.h"
#include <map>
#include <type_traits>

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
        size_t GetTypeSize();
        template<class T>
        T* CreateObjectOfTypeInternal(const std::string &name);

        void DeleteObjectInternal(LightRayObject *object);

        int m_idCounter{};
        std::map<size_t, size_t> m_typeHashToTypeSize;
        std::map<int, void*> m_objectsContainer;
    };

    template<class T>
    size_t ObjectManager::GetTypeSize() {
        const std::type_info &typeInfo = typeid(T);
        size_t typeHash = typeInfo.hash_code();
        if (!m_typeHashToTypeSize.contains(typeHash)) {
            m_typeHashToTypeSize[typeHash] = sizeof(T);
        }

        return m_typeHashToTypeSize[typeHash];
    }

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
    T* ObjectManager::CreateObjectOfTypeInternal(const std::string &name) {
        static_assert(std::is_base_of<LightRayObject, T>());

        size_t typeSize = GetTypeSize<T>();
        void* ptr = malloc(typeSize);
        T* objectPtr = (T*) ptr;
        objectPtr(m_idCounter);
        objectPtr->name = name;
        m_objectsContainer[m_idCounter] = ptr;
        m_idCounter++;

        return ptr;
    }
} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_OBJECTMANAGER_H
