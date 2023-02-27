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

            if (transform_attach->attach_type == AttachType::ANCHRED)
            {
                transform_component->position.x = 0;
                transform_component->position.y = 0;
                transform_component->rotation_z = 0;
            }

            // TODO: relative movement
            transform_component->rotation_z
              += attach_transform_component->rotation_z + transform_attach->rotation_z_offset;

            //            transform_component->position
            //              = attach_transform_component->position +
            //              transform_attach->position_offset;

            auto cos_angle = cos(transform_component->rotation_z);
            auto sin_angle = sin(transform_component->rotation_z);

            transform_component->position.x += attach_transform_component->position.x
                                               + cos_angle * transform_attach->position_offset.x
                                               - sin_angle * transform_attach->position_offset.y;

            transform_component->position.y += attach_transform_component->position.y
                                               + sin_angle * transform_attach->position_offset.x
                                               + cos_angle * transform_attach->position_offset.y;

            //            setRotationAngle(element, angle, x, y):
            //              setRotationAngle(element, angle)
            //              step_x = cos(angle) * (element.x - x) - sin(angle) * (element.y - y)
            //              step_y = sin(angle) * (element.x - x) + cos(angle) * (element.y - y)
            //              moveElement(element, step_x, step_y)
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
