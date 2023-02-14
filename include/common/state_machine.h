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

class StateMachine
{
public:
    StateMachine(StateBehavior a_state_behavior){};

    // Tries to change state. If can't, set false:=
    static bool enterState(StateBehavior a_state_behavior, State& a_from_state, State a_to_state);

    // Gets end animation
    static State endState(State& a_state);
};


// Add StateComponent that only holds current component and component Behavior
