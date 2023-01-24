#pragma once
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class TransformComponent : public Component
{
public:
    TransformComponent(Entity& a_entity, const Vec2D& a_position, double a_rotation_z)
      : Component(a_entity)
      , position(a_position)
      , rotation_z(a_rotation_z){};

    Vec2D position;
    double rotation_z;
};
