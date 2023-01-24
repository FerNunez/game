#pragma once

#include "../helper/ecs.h"
#include <chrono>

class DestroyableByTimeComponent : public Component
{
public:
    DestroyableByTimeComponent(Entity& a_entity, double a_duration_ms)
      : Component(a_entity)
      , duration_ms(a_duration_ms)
      , start_time(std::chrono::steady_clock::now()){};

    double duration_ms;
    std::chrono::time_point<std::chrono::steady_clock> start_time;
};
