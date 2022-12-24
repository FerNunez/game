#pragma once

#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class RigidBodyComponent : public Component
{
public:
    RigidBodyComponent(Entity& a_entity, const Vec2D& a_velocity, const Vec2D& a_acceleration)
      : Component(a_entity)
      , velocity(a_velocity)
      , acceleration(a_acceleration){};

    Vec2D velocity;
    Vec2D acceleration;
};
