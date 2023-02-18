#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

#include "../common/state_machine.h"

class PhysicsSystem : public System
{
public:
    PhysicsSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            RigidBodyComponent* rigid_body_component = entity->GetComponent<RigidBodyComponent>();
            StateComponent* state_component = entity->GetComponent<StateComponent>();

            if (transform_component == nullptr)
            {
                continue;
            }
            if (rigid_body_component == nullptr)
            {
                continue;
            }

            if (state_component == nullptr)
            {
                transform_component->position
                  = transform_component->position + rigid_body_component->velocity * 2 * dt;

                continue;
            }

            // TODO: FIX
            if (state_component == nullptr)
            {
                continue;
            }
            if (rigid_body_component->velocity.x == 0 && rigid_body_component->velocity.y == 0)
            {
                StateMachine::enterState(
                  state_component->state_behavior, state_component->current_state, State::IDLE);
            }
            else
            {
                if(!StateMachine::enterState(
                      state_component->state_behavior, state_component->current_state, State::WALK))
                {continue;}

                transform_component->position
                  = transform_component->position + rigid_body_component->velocity * 2 * dt;

                if (rigid_body_component->velocity.x > 0)
                {
                    // TODO: set direction
                    StateMachine::setDirection(state_component->facing_direction,
                                               FacingDirection::RIGHT);
                }
                else if (rigid_body_component->velocity.x < 0)
                {
                    // TODO: set direction
                    StateMachine::setDirection(state_component->facing_direction,
                                               FacingDirection::LEFT);
                }
                else if (rigid_body_component->velocity.y > 0)
                {
                    // TODO: set Direction
                    StateMachine::setDirection(state_component->facing_direction,
                                               FacingDirection::DOWN);
                }
                else if (rigid_body_component->velocity.y < 0)
                {
                    // TODO: set Direction
                    StateMachine::setDirection(state_component->facing_direction,
                                               FacingDirection::UP);
                }
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
