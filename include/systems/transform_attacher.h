#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

#include "../common/state_machine.h"

class TransformAttacherSystem : public System
{
public:
    TransformAttacherSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            RigidBodyComponent* rigid_body_component = entity->GetComponent<RigidBodyComponent>();

            TransformAttachComponent* transform_attach
              = entity->GetComponent<TransformAttachComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (transform_attach == nullptr)
            {
                continue;
            }

            Entity* attached_to = transform_attach->attached_to_entity;
            TransformComponent* attach_transform_component
              = attached_to->GetComponent<TransformComponent>();

            if (attach_transform_component == nullptr)
            {
                continue;
            }

            // TODO: relative movement
            transform_component->position
              = attach_transform_component->position + transform_attach->position_offset;
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
