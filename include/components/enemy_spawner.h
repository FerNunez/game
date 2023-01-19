#pragma once
#include "../helper/ecs.h"
#include <chrono>

class EnemySpawnerComponent : public Component
{
public:
    EnemySpawnerComponent(Entity& a_entity,
                          int a_number_enemies,
                          double a_spawn_cooldown_duration_ms)
      : Component(a_entity)
      , number_enemies(a_number_enemies)
      , spawn_cooldown_duration_ms(a_spawn_cooldown_duration_ms)
      , last_spawn(std::chrono::steady_clock::now()){};

    int number_enemies;
    double spawn_cooldown_duration_ms;
    std::chrono::time_point<std::chrono::steady_clock> last_spawn;
};
