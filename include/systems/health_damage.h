#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class HealthDamageSystem : public System
{
public:
    HealthDamageSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            HealthComponent* health_component = entity->GetComponent<HealthComponent>();
            SufferDamageComponent* suffer_damage_component
              = entity->GetComponent<SufferDamageComponent>();

            if (health_component == nullptr)
            {
                continue;
            }

            if (suffer_damage_component == nullptr)
            {
                continue;
            }

            if (suffer_damage_component->damage > 0)
            {
                health_component->current_health -= suffer_damage_component->damage;
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
