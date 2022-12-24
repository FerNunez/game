#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class CleanerSystem : public System
{
public:
    CleanerSystem(std::vector<std::shared_ptr<Entity>> entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : m_entities)
        {
            ColliderComponent* collider_component = entity->GetComponent<ColliderComponent>();

            if (collider_component == nullptr)
            {
                continue;
            }

            collider_component->entities_collided_to.clear();
        }
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};
