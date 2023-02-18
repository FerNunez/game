#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class SpriteRenderComponent : public Component
{
public:
    SpriteRenderComponent(Entity& a_entity,
                          bool a_visible,
                          std::string a_sprite_path,
                          double a_width,
                          double a_height,
                          const Vec2D& a_scale)
      : Component(a_entity)
      , visible(a_visible)
      , width(a_width)
      , height(a_height)
      , scale(a_scale)
      , flip(false)
    {

        SDL_Surface* spriteSurface = IMG_Load(a_sprite_path.c_str());
        sprite_texture = SDL_CreateTextureFromSurface(g_game_state.renderer, spriteSurface);
        SDL_FreeSurface(spriteSurface);

        rect_src = { 0, 0, static_cast<int>(width), static_cast<int>(height) };
    };

    ~SpriteRenderComponent()
    {
        SDL_DestroyTexture(sprite_texture);
    }

    // to render
    bool visible;
    SDL_Texture* sprite_texture;
    double width;
    double height;
    Vec2D scale;
    bool flip;
    SDL_Rect rect_src;
};
