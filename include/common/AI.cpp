#include "AI.h"

AI::AI(AIBehaviorType a_behavior)
  : current_state(AIState::IDLE)
  , prev_action(AIState::IDLE)
  , behavior(a_behavior)
  , destination(Vec2D(0, 0))
  , deplacement(Vec2D(0, 0))
  , time_point(std::chrono::steady_clock::now())
{
    generator.seed(std::random_device()());
    distribution = std::normal_distribution<double>(0, 5);
}

void AI::computeIteration(TransformComponent* a_tranform_component,
                          RigidBodyComponent* a_rigid_body_component)
{
    Vec2D point_A(10, 10);
    Vec2D point_B(-10, 0);

    // CASE RANDOM
    switch (current_state)
    {
    case AIState::IDLE:
    {
        // GetNew location
        switch (prev_action)
        {
        case AIState::IDLE:
        case AIState::MOVE:
        {
            deplacement = computeRandomVec2DMovement(20);
            current_state = AIState::MOVE;
            prev_action = AIState::COMEBACK;
            break;
        }
        case AIState::COMEBACK:
        default:
            deplacement = deplacement * (-1) + computeRandomVec2DMovement(5);

            current_state = AIState::COMEBACK;
            prev_action = AIState::MOVE;

            break;
        }

        destination = a_tranform_component->position + deplacement;
        a_rigid_body_component->velocity = deplacement.normalize();
        break;
    case AIState::COMEBACK:
    case AIState::MOVE:
        // Check if arrived to destination

        if (computeDistance(a_tranform_component->position, destination) < 1)
        {
            a_rigid_body_component->velocity = Vec2D(0, 0);
            time_point = std::chrono::steady_clock::now();
            current_state = AIState::WAIT;
        }
        break;
    case AIState::WAIT:
        // Already waited enoguh?
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
                                                                  - time_point)
              .count()
            > wait_duration_ms)
        {
            current_state = AIState::IDLE;
        }
        break;
    default:
        break;
    }
    }
}

Vec2D AI::computeRandomVec2DMovement(double radious)
{

    double movement_x = distribution(generator) * radious; // distribution(generator);
    double movement_y = distribution(generator) * radious; // distribution(generator);

    return Vec2D(movement_x, movement_y);
}

double AI::computeDistance(const Vec2D& position_a, const Vec2D& position_b)
{
    Vec2D difference = position_a - position_b;
    return difference.length();
}
