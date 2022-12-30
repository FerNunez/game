#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class RendererSystem : public System
{
public:
    RendererSystem(std::vector<std::shared_ptr<Entity>> entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : m_entities)
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

            // TODO: CONVERT FROM WOLRD TO IMAGE

            SDL_Rect rect
              = { static_cast<int>(transform_component->position.x - square_render->width / 2),
                  static_cast<int>(transform_component->position.y - square_render->height / 2),
                  static_cast<int>(square_render->width),
                  static_cast<int>(square_render->height) };

            // Render the square.

            Uint8 r, g, b, a;
            SDL_GetRenderDrawColor(square_render->renderer, &r, &g, &b, &a);

            SDL_SetRenderDrawColor(square_render->renderer,
                                   square_render->color.r,
                                   square_render->color.g,
                                   square_render->color.b,
                                   square_render->color.alpha);

            SDL_RenderFillRect(square_render->renderer, &rect);

            SDL_SetRenderDrawColor(square_render->renderer, r, g, b, a);
        }
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};