#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class DamageGeneratorSystem : public System
{
public:
    DamageGeneratorSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {

            CollidedComponent* collided_component = entity->GetComponent<CollidedComponent>();
            HealthComponent* health_component = entity->GetComponent<HealthComponent>();

            if (collided_component == nullptr || health_component == nullptr)
            {
                continue;
            }

            SufferDamageComponent* suffer_damage_component
              = entity->GetComponent<SufferDamageComponent>();

            for (auto collided_with_entity : collided_component->entities_collided_with)
            {
                DoDamageComponent* do_damage_component
                  = collided_with_entity->GetComponent<DoDamageComponent>();

                if (do_damage_component == nullptr)
                {
                    continue;
                }

                if (suffer_damage_component == nullptr)
                {
                    std::shared_ptr<SufferDamageComponent> new_suffer_damage_component
                      = std::make_shared<SufferDamageComponent>(*entity, 0);
                    entity->AddComponent(new_suffer_damage_component);

                    suffer_damage_component = new_suffer_damage_component.get();
                }

                suffer_damage_component->damage += do_damage_component->damage;
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
