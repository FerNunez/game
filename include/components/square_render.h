#pragma once
#include <SDL2/SDL.h>

#include "../helper/color.h"
#include "../helper/ecs.h"

class SquareRenderComponent : public Component
{
public:
    SquareRenderComponent(Entity& a_entity,
                          bool a_visible,
                          double a_width,
                          double a_height,
                          const Color& a_color)
      : Component(a_entity)
      , visible(a_visible)
      , width(a_width)
      , height(a_height)
      , color(a_color){};

    // to render
    bool visible;

    // more infor about rendering:
    // sprint?

    double width;
    double height;
    Color color;
};
