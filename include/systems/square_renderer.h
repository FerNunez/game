#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class SquareRendererSystem : public System
{
public:
    SquareRendererSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            SquareRenderComponent* square_render = entity->GetComponent<SquareRenderComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (square_render == nullptr)
            {
                continue;
            }

            if (!square_render->visible)
            {
                continue;
            }
            // TODO: CONVERT FROM WOLRD TO IMAGE

            SDL_Rect rect
              = { static_cast<int>(transform_component->position.x - square_render->width / 2),
                  static_cast<int>(transform_component->position.y - square_render->height / 2),
                  static_cast<int>(square_render->width),
                  static_cast<int>(square_render->height) };

            // Render the square.
            SDL_SetRenderDrawBlendMode(g_game_state.renderer, SDL_BLENDMODE_BLEND);
            Uint8 r, g, b, a;
            SDL_GetRenderDrawColor(g_game_state.renderer, &r, &g, &b, &a);

            SDL_SetRenderDrawColor(g_game_state.renderer,
                                   square_render->color.r,
                                   square_render->color.g,
                                   square_render->color.b,
                                   square_render->color.alpha);

            SDL_RenderFillRect(g_game_state.renderer, &rect);

            SDL_SetRenderDrawColor(g_game_state.renderer, r, g, b, a);
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
