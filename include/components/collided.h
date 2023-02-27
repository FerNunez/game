#pragma once
#include <memory>
#include <vector>

#include "../helper/ecs.h"

class CollidedComponent : public Component
{
public:
    CollidedComponent(Entity& a_entity)
      : Component(a_entity)
    {
        entities_collided_with = {};
    };

    CollidedComponent(Entity& a_entity, Entity* a_collided_with_entity)
      : Component(a_entity)
    {
        entities_collided_with.push_back(a_collided_with_entity);
    };

    std::vector<Entity*> entities_collided_with;
};
