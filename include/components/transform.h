#pragma once
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class TransformComponent : public Component
{
public:
    TransformComponent(Entity& a_entity,
                       const Vec2D& a_position,
                       const Vec2D& a_rotation,
                       const Vec2D& a_scale)
      : Component(a_entity)
      , position(a_position)
      , rotation(a_rotation)
      , scale(a_scale){};

    Vec2D position;
    Vec2D rotation;
    Vec2D scale;
};
