#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../helper/ecs.h"
#include "../common/state_machine.h"

class DestroyByTimeSystem : public System
{
public:
    DestroyByTimeSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            DestroyableByTimeComponent* destroyable_after_time_component
              = entity->GetComponent<DestroyableByTimeComponent>();
            SquareRenderComponent* square_render_component
              = entity->GetComponent<SquareRenderComponent>();
            SpriteRenderComponent* sprite_render_component
              = entity->GetComponent<SpriteRenderComponent>();
            CollidableComponent* collidable_component = entity->GetComponent<CollidableComponent>();



            if (destroyable_after_time_component == nullptr || collidable_component == nullptr)
            {
                continue;
            }

            if (std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::steady_clock::now() - destroyable_after_time_component->start_time)
                  .count()
                >= destroyable_after_time_component->duration_ms)
            {
                collidable_component->collidable = false;

                if (square_render_component != nullptr)
                {
                    square_render_component->visible = false;
                }

                if (sprite_render_component != nullptr)
                {
                    sprite_render_component->visible = false;
                }

            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
