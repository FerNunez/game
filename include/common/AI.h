#pragma once

#include "../helper/ecs.h"
#include "../helper/vec2d.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <random>

#include "../components/rigid_body.h"
#include "../components/transform.h"

enum class AIState
{
    IDLE,
    WAIT,
    SEARCH_FOR,
    COMPUTE_MOVE_TARGET,
    MOVE,
    COMEBACK,
    ATTACK,
    RESET,
    _NUM_AI_STATES
};

enum class AIBehaviorType
{
    RANDOM,
    RUNNER,
    KILLER,
    _NUM_AI_BEHAVIORS
};

class AI
{
public:
    AI(AIBehaviorType a_behavior);

    void computeIteration(TransformComponent* a_tranform_component,
                          RigidBodyComponent* a_rigid_body_component);

private:
    AIState current_state;
    AIState prev_action;

    AIBehaviorType behavior;

    // Randomness
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    Vec2D destination;

    Vec2D deplacement;
    // wait
    double wait_duration_ms = 2500;
    std::chrono::time_point<std::chrono::steady_clock> time_point;

    // computes vector direction
    Vec2D computeRandomVec2DMovement(double radious);

    double computeDistance(const Vec2D& position_a, const Vec2D& position_b);
};
