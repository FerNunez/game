#pragma once

#include "../common/bezier.h"
#include "../helper/ecs.h"
#include <chrono>

class TrajectoryFollowComponent : public Component
{
public:
    TrajectoryFollowComponent(Entity& a_entity,
                              const Trajectory& a_trajectory,
                              std::uint64_t a_duration_ms)
      : Component(a_entity)
      , trajectory(a_trajectory)
      , duration_ms(a_duration_ms)
      , init_time(std::chrono::steady_clock::now())
    {
        trajetory_size = a_trajectory.points.size();
    };

    Trajectory trajectory;
    std::uint64_t duration_ms;
    std::chrono::time_point<std::chrono::steady_clock> init_time;

    int trajetory_size;
};
