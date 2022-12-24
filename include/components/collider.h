#pragma once
#include <memory>

#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class ColliderComponent : public Component
{
public:
    ColliderComponent(Entity& a_entity, bool a_collidable, double a_width, double a_height)
      : Component(a_entity)
      , collidable(a_collidable)
      , width(a_width)
      , height(a_height)
      /*, colliding(false)*/ {};

    bool collidable;
    double width;
    double height;
    //    bool colliding;

    // TODO: RESERVE SPACE FOR VECTOR
    std::vector<std::shared_ptr<Entity>> entities_collided_to{};
};
