#pragma once
#include "../helper/ecs.h"
#include "../common/AI.h"

class AIBehaviorComponent : public Component
{
public:
    AIBehaviorComponent(Entity& a_entity, AIBehaviorType a_behavior_type)
      : Component(a_entity)
      , ai(AI(a_behavior_type)){};

    AI ai;
};
