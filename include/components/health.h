#pragma once

#include "../helper/ecs.h"

class HealthComponent : public Component
{
public:
    HealthComponent(Entity& a_entity, double a_max_health, double a_current_health)
      : Component(a_entity)
      , max_health(a_max_health)
      , current_health(a_current_health){};

    double max_health;
    double current_health;
};
