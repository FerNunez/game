#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class SpriteRendererSystem : public System
{
public:
    SpriteRendererSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            SpriteRenderComponent* sprite_renderer = entity->GetComponent<SpriteRenderComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (sprite_renderer == nullptr)
            {
                continue;
            }

            if (!sprite_renderer->visible)
            {
                continue;
            }
            // TODO: CONVERT FROM WOLRD TO IMAGE

            SDL_Rect rect_src = sprite_renderer->rect_src;

            SDL_Rect rect_dest
              = { static_cast<int>(transform_component->position.x
                                   - (sprite_renderer->width * sprite_renderer->scale.x) / 2),
                  static_cast<int>(transform_component->position.y
                                   - sprite_renderer->height * sprite_renderer->scale.y / 2),
                  static_cast<int>(sprite_renderer->width * sprite_renderer->scale.x),
                  static_cast<int>(sprite_renderer->height * sprite_renderer->scale.y) };
            SDL_RendererFlip renderer_flip
              = (sprite_renderer->flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            SDL_RenderCopyEx(g_game_state.renderer,
                             sprite_renderer->sprite_texture,
                             &rect_src,
                             &rect_dest,
                             transform_component->rotation_z * 180.0 / M_PI,
                             NULL,
                             renderer_flip);
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
