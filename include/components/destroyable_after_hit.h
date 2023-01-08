#pragma once

#include "../helper/ecs.h"

class DestroyableAfterHitComponent : public Component
{
public:
    DestroyableAfterHitComponent(Entity& a_entity, int a_number_remaining_hits_before_die )
      : Component(a_entity)
      , number_remaining_hits_before_die(a_number_remaining_hits_before_die)
{};

    int number_remaining_hits_before_die;
};
