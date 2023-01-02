#pragma once
#include "../helper/ecs.h"

// enum DamageType
//{
//    NORMAL,
//    FIRE,
//    ICE,
//    _NUM_DAMAGE_TYPE
//};

class SufferDamageComponent : public Component
{
public:
    SufferDamageComponent(Entity& a_entity, double a_damage /*, DamageType a_damage_type*/)
      : Component(a_entity)
      , damage(a_damage)
      /*, damage_type(a_damage_type)*/ {};

    double damage;
    //    DamageType damage_type;
};
