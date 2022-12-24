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
    CollisionSystem(std::vector<std::shared_ptr<Entity>> entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (int idx(0); idx < m_entities.size(); idx++)
        {
            auto entity = m_entities[idx];
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

            for (int idx2(idx + 1); idx2 < m_entities.size(); idx2++)
            {
                auto another_entity = m_entities[idx2];

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

                if (Collide(transform_component->position,
                            collider_component->width,
                            collider_component->height,
                            another_transform_component->position,
                            another_collider_component->width,
                            another_collider_component->height))
                {

                    collider_component->entities_collided_to.push_back(another_entity);

                    another_collider_component->entities_collided_to.push_back(entity);
                }
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};
