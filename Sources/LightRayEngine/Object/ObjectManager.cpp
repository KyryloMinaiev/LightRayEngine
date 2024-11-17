//
// Created by MrFlyingChip on 15.11.2024.
//

#include "ObjectManager.h"

namespace LightRayEngine {
    ObjectManager *ObjectManager::s_instance;

    ObjectManager::ObjectManager() : m_idCounter(0) {
        s_instance = this;
    }

    void ObjectManager::DeleteObject(LightRayObject *object) {
        s_instance->DeleteObjectInternal(object);
    }

    void ObjectManager::DeleteObjectInternal(LightRayObject *object) {
        if (!object) {
            return;
        }

        int objID = object->GetID();
        if(!m_objectsContainer.contains(objID)){
            return;
        }

        void* ptr = m_objectsContainer[objID];
        object->~LightRayObject();

        free(ptr);
    }

    ObjectManager::~ObjectManager() {
        m_idCounter = 0;
        for (const auto& objContainer : m_objectsContainer) {
            free(objContainer.second);
        }
    }
} // LightRayEngine