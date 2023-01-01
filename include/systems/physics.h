#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class PhysicsSystem : public System
{
public:
    PhysicsSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            RigidBodyComponent* rigid_body_component = entity->GetComponent<RigidBodyComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (rigid_body_component == nullptr)
            {
                continue;
            }

            transform_component->position
              = transform_component->position + rigid_body_component->velocity * dt;
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
