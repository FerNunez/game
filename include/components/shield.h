#pragma once
#include "../helper/ecs.h"

enum ShieldType
{
    NORMAL,
    FIRE,
    ICE,
    _NUM_shield_TYPE
};

class ShieldComponent : public Component
{
public:
    ShieldComponent(Entity& a_entity, double a_shield, ShieldType a_shield_type)
      : Component(a_entity)
      , shield(a_shield)
      , shield_type(a_shield_type){};

    double shield;
    ShieldType shield_type;
};
