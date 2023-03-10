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
    CleanerSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            CollidedComponent* collided_component = entity->GetComponent<CollidedComponent>();
            SufferDamageComponent* suffer_damage_component
              = entity->GetComponent<SufferDamageComponent>();

            if (collided_component != nullptr)
            {
                collided_component->entities_collided_with.clear();
            }

            if (suffer_damage_component != nullptr)
            {
                suffer_damage_component->damage = 0;
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
