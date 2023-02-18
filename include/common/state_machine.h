#pragma once

enum class StateBehavior
{
    PLAYER,
    ENEMY
};
enum class State
{
    IDLE,
    WAIT,
    WALK,
    ATTACK,
    REST,
    DEATH
};

enum class FacingDirection
{
    NONE,
    LEFT,
    DOWN,
    UP,
    RIGHT
};

class StateMachine
{
public:
    StateMachine(){};

    // Tries to change state. If can't, set false:=
    static bool enterState(StateBehavior a_state_behavior, State& a_from_state, State a_to_state);

    // Gets end animation
    static void endState(StateBehavior a_state_behavior, State& a_state);

    // TODO: state machine to check if facing direction can return false
    static bool setDirection(FacingDirection& a_current_direction, FacingDirection a_new_direction);
};

// Add StateComponent that only holds current component and component Behavior
