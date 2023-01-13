#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class AISystem : public System
{
public:
    AISystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            AIBehaviorComponent* ai_behavior_component = entity->GetComponent<AIBehaviorComponent>();
            RigidBodyComponent* rigid_body_component = entity->GetComponent<RigidBodyComponent>();
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();

            if(ai_behavior_component == nullptr || rigid_body_component == nullptr || transform_component == nullptr)
            {
                continue;
            }

                ai_behavior_component->ai.computeIteration(transform_component, rigid_body_component);

                //if AI has weapon:and if state is can_attack- attack!
            /*computeIteration()*/
        }

    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
