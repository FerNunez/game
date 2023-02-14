#pragma once

#include "../common/state_machine.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class StateComponent : public Component
{
public:
    StateComponent(Entity& a_entity, StateBehavior a_state_behavior, State a_current_state)
      : Component(a_entity)
      , state_behavior(a_state_behavior)
      , current_state(a_current_state){};

    StateBehavior state_behavior;
    State current_state;
};
