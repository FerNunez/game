#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/collide.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class CollisionSystem : public System
{
public:
    CollisionSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (int idx(0); idx < m_entities->size(); idx++)
        {
            auto entity = (*m_entities)[idx];
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            ColliderComponent* collider_component = entity->GetComponent<ColliderComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (collider_component == nullptr)
            {
                continue;
            }

            for (int idx2(idx + 1); idx2 < m_entities->size(); idx2++)
            {
                auto another_entity = (*m_entities)[idx2];

                TransformComponent* another_transform_component
                  = another_entity->GetComponent<TransformComponent>();
                ColliderComponent* another_collider_component
                  = another_entity->GetComponent<ColliderComponent>();

                if (another_transform_component == nullptr)
                {
                    continue;
                }
                if (another_transform_component == nullptr)
                {
                    continue;
                }

                if (collider_component->collision_group
                    == another_collider_component->collision_group)
                {
                    continue;
                }

                if (Collide(transform_component->position,
                            collider_component->width,
                            collider_component->height,
                            another_transform_component->position,
                            another_collider_component->width,
                            another_collider_component->height))
                {

                    // Entity takes damage if has health and another entity does damages
                    HealthComponent* health_component = entity->GetComponent<HealthComponent>();
                    DoDamageComponent* another_do_damage_component
                      = another_entity->GetComponent<DoDamageComponent>();

                    if (health_component != nullptr && another_do_damage_component != nullptr)
                    {

                        std::shared_ptr<SufferDamageComponent> suffer_damage
                          = std::make_shared<SufferDamageComponent>(
                            *entity, another_do_damage_component->damage);
                        entity->AddComponent(suffer_damage);

                        // TODO: If projectil: dissapear
                        std::cout << entity->name() << " suffers: " << suffer_damage->damage
                                  << std::endl;
                    }

                    // Another entity takes damage if it has health and if entity does damages
                    HealthComponent* another_health_component
                      = another_entity->GetComponent<HealthComponent>();
                    DoDamageComponent* do_damage_component
                      = entity->GetComponent<DoDamageComponent>();

                    if (another_health_component != nullptr && do_damage_component != nullptr)
                    {
                        std::shared_ptr<SufferDamageComponent> suffer_damage
                          = std::make_shared<SufferDamageComponent>(*entity,
                                                                    do_damage_component->damage);
                        another_entity->AddComponent(suffer_damage);

                        // TODO: If projectil: dissapear
                        std::cout << another_entity->name() << " suffers: " << suffer_damage->damage
                                  << std::endl;
                    }

                    //                    collider_component->entities_collided_to.push_back(another_entity);

                    //                    another_collider_component->entities_collided_to.push_back(entity);
                }
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
