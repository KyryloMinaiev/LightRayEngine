//
// Created by MrFlyingChip on 17.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_TYPEMANAGER_H
#define LIGHTRAYAPPLICATION_TYPEMANAGER_H

#include <map>
#include <typeinfo>

namespace LightRayEngine {
    class TypeManager {
    public:
        template<class T>
        static size_t GetTypeSize();

        template<class T>
        static size_t GetTypeHash();
    private:
        static std::map<size_t, size_t> m_typeHashToTypeSize;
    };

    template<class T>
    size_t TypeManager::GetTypeHash() {
        const std::type_info &typeInfo = typeid(T);
        return typeInfo.hash_code();
    }

    template<class T>
    size_t TypeManager::GetTypeSize() {
        size_t typeHash = GetTypeHash<T>();
        if (!m_typeHashToTypeSize.contains(typeHash)) {
            m_typeHashToTypeSize[typeHash] = sizeof(T);
        }

        return m_typeHashToTypeSize[typeHash];
    }

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_TYPEMANAGER_H
