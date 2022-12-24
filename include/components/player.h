#pragma once

#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class PlayerComponent : public Component
{
public:
    PlayerComponent(Entity& a_entity)
      : Component(a_entity)
      , is_player(true){};

    bool is_player;
    
};
