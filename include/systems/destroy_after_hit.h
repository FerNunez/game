#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class DestroyAfterHitSystem : public System
{
public:
    DestroyAfterHitSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            DestroyableAfterHitComponent* destroyable_after_hit_component
              = entity->GetComponent<DestroyableAfterHitComponent>();
            CollidedComponent* collided_component = entity->GetComponent<CollidedComponent>();
            SquareRenderComponent* square_render_component
              = entity->GetComponent<SquareRenderComponent>();
            SpriteRenderComponent* sprite_render_component
              = entity->GetComponent<SpriteRenderComponent>();

            CollidableComponent* collidable_component = entity->GetComponent<CollidableComponent>();

            if (destroyable_after_hit_component == nullptr || collided_component == nullptr
                || collidable_component == nullptr)
            {
                continue;
            }

            destroyable_after_hit_component->number_remaining_hits_before_die
              -= collided_component->entities_collided_with.size();

            if (destroyable_after_hit_component->number_remaining_hits_before_die <= 0)
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
