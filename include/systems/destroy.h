#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class DestroySystem : public System
{
public:
    DestroySystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            HealthComponent* health_component = entity->GetComponent<HealthComponent>();
            SquareRenderComponent* square_render_component
              = entity->GetComponent<SquareRenderComponent>();
            CollidableComponent* collidable_component = entity->GetComponent<CollidableComponent>();

            if (health_component == nullptr || square_render_component == nullptr
                || collidable_component == nullptr)
            {
                continue;
            }

            if (health_component->current_health <= 0)
            {
                collidable_component->collidable = false;
                square_render_component->visible = false;
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
