//
// Created by MrFlyingChip on 10.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_COMPONENT_H
#define LIGHTRAYAPPLICATION_COMPONENT_H

#include "Object/LightRayObject.h"

namespace LightRayEngine {
    class Entity;

    class Component : public LightRayObject {
    public:
        explicit Component(int objectID) : LightRayObject(objectID) {
            m_entity = nullptr;
        };

        ~Component() override = default;

        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update() {};
        virtual void LateUpdate() {};
        virtual void OnEnable() {};
        virtual void OnDisable() {};
        virtual void OnDestroy() {};

        void SetEntity(Entity *entity) {
            m_entity = entity;
        }

        [[nodiscard]] Entity *GetEntity() const {
            return m_entity;
        }

    private:
        Entity *m_entity;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_COMPONENT_H
