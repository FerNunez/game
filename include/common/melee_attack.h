#pragma once
#include "bezier.h"

enum class MeleeAttackWeapon
{
    SPEAR,
    SWORD
};

enum class MeleeAttackType
{
    SINGLE,
    DOUBLE,
    AROUND
};

std::vector<TrajectoryPoint> generateTrajectory(MeleeAttackWeapon weapon, MeleeAttackType attack_type)
{
    std::vector<float> T = Bezier::computeT(50, TrajectoryVelocityType::QUADRATIC);
    std::vector<TrajectoryPoint> trajectory = Bezier::computeTrajectory(
      T, vec2f(-5.0f, 0.0f), vec2f(-5.0f, -5.0f), vec2f(5.0f, -5.0f), vec2f(5.0f, 0.0f));

    return trajectory;
}
