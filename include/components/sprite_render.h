#pragma once
#include <SDL2/SDL.h>

#include "../helper/color.h"
#include "../helper/ecs.h"

class SpriteRenderComponent : public Component
{
public:
    SpriteRenderComponent(Entity& a_entity,
                          SDL_Renderer* a_renderer,
                          bool a_visible,
                          string a_sprite,
                          double a_width,
                          double a_height,
                          const Color& a_color)
      : Component(a_entity)
      , renderer(a_renderer)
      , visible(a_visible)
      , width(a_width)
      , height(a_height)
      , color(a_color){};

    // to render
    bool visible;
    SDL_Renderer* renderer;

    // more infor about rendering:
    // sprint?
    double width;
    double height;
    Color color;
};
