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
            Entity* entity = (*m_entities)[idx].get();
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            CollidableComponent* collidable_component = entity->GetComponent<CollidableComponent>();
            CollidedComponent* collided_component = entity->GetComponent<CollidedComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (collidable_component == nullptr)
            {
                continue;
            }

            for (int idx2(idx + 1); idx2 < m_entities->size(); idx2++)
            {
                Entity* another_entity = (*m_entities)[idx2].get();

                TransformComponent* another_transform_component
                  = another_entity->GetComponent<TransformComponent>();
                CollidableComponent* another_collidable_component
                  = another_entity->GetComponent<CollidableComponent>();
                CollidedComponent* another_collided_component
                  = another_entity->GetComponent<CollidedComponent>();

                if (another_transform_component == nullptr)
                {
                    continue;
                }
                if (another_transform_component == nullptr)
                {
                    continue;
                }

                if (collidable_component->collidable == false
                    || another_collidable_component->collidable == false)
                {
                    continue;
                }

                if (collidable_component->collision_group
                    == another_collidable_component->collision_group)
                {
                    continue;
                }

                if (Collide(transform_component->position,
                            collidable_component->width,
                            collidable_component->height,
                            another_transform_component->position,
                            another_collidable_component->width,
                            another_collidable_component->height))
                {
                    if (collided_component == nullptr)
                    {
                        std::shared_ptr<CollidedComponent> collided
                          = std::make_shared<CollidedComponent>(*entity);
                        entity->AddComponent(collided);
                    }
                    CollidedComponent* collided = entity->GetComponent<CollidedComponent>();
                    collided->entities_collided_with.push_back(another_entity);

                    if (another_collided_component == nullptr)
                    {
                        std::shared_ptr<CollidedComponent> another_collided
                          = std::make_shared<CollidedComponent>(*another_entity);
                        another_entity->AddComponent(another_collided);
                    }
                    CollidedComponent* another_collided
                      = another_entity->GetComponent<CollidedComponent>();
                    another_collided->entities_collided_with.push_back(entity);
                }
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
