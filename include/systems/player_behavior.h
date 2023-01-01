#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class PlayerBehaviorSystem : public System
{
public:
    PlayerBehaviorSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            PlayerComponent* player_component = entity->GetComponent<PlayerComponent>();
            RigidBodyComponent* rigid_body_component = entity->GetComponent<RigidBodyComponent>();

            if (player_component == nullptr)
            {
                continue;
            }
            if (rigid_body_component == nullptr)
            {
                continue;
            }

            rigid_body_component->velocity = Vec2D(
              g_game_state.velocity_constant * (g_game_state.move_right - g_game_state.move_left),
              g_game_state.velocity_constant * (g_game_state.move_down - g_game_state.move_up));
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
