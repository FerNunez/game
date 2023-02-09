#pragma once
#include <memory>

#include "../helper/ecs.h"
#include "../helper/vec2d.h"

enum class CollisionGroup
{
    FRIEND,
    ENEMY,
    _NUM_COLLISION_GROUP
};

enum class CollisionType
{
    AABB,
    SAT,
    _NUM_COLLISION_TYPES
};

class CollidableComponent : public Component
{
public:
    CollidableComponent(Entity& a_entity,
                        bool a_collidable,
                        double a_width,
                        double a_height,
                        CollisionGroup a_collision_group)
      : Component(a_entity)
      , collidable(a_collidable)
      , width(a_width)
      , height(a_height)
      , collision_group(a_collision_group)
      , collision_type(CollisionType::AABB){};

    CollidableComponent(Entity& a_entity,
                        bool a_collidable,
                        double a_width,
                        double a_height,
                        CollisionGroup a_collision_group,
                        CollisionType a_collision_type)
      : Component(a_entity)
      , collidable(a_collidable)
      , width(a_width)
      , height(a_height)
      , collision_group(a_collision_group)
      , collision_type(a_collision_type){};

    bool collidable;
    double width;
    double height;
    CollisionGroup collision_group;
    CollisionType collision_type;
};
