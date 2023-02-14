#include "state_machine.h"

bool StateMachine::enterState(StateBehavior a_state_behavior, State& a_from_state, State a_to_state)
{
    if (a_from_state == a_to_state)
    {
        return true;
    }

    switch (a_state_behavior)
    {
    case StateBehavior::PLAYER:
    {
        if (a_from_state == State::IDLE)
        {
            switch (a_to_state)
            {
            case State::WALK:
            case State::ATTACK:
            case State::DEATH:
                a_from_state = a_to_state;
                return true;
            default:
                return false;
            }
        }

        if (a_from_state == State::WALK)
        {
            switch (a_to_state)
            {
            case State::IDLE:
                //            case State::DEATH:
                a_from_state = a_to_state;
                return true;
            default:
                return false;
            }
        }

        if (a_from_state == State::ATTACK)
        {
            switch (a_to_state)
            {
            case State::IDLE:
                //            case State::DEATH:
                a_from_state = a_to_state;
                return true;
            default:
                return false;
            }
        }
    }
    break;
    default:
        return false;
    }
}

// Add StateComponent that only holds current component and component Behavior
