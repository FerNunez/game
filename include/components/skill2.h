#pragma once
#include "../common/skills.h"
#include "../helper/ecs.h"
#include <chrono>

class Skill2Component : public Component
{
public:
    Skill2Component(Entity& a_entity, SkillType a_skill_type, std::uint32_t a_cooldown_duration_ms)
      : Component(a_entity)
      , skill_type(a_skill_type)
      , cooldown_duration_ms(a_cooldown_duration_ms)
      , timepoint(std::chrono::steady_clock::now()){};

    SkillType skill_type;
    std::uint32_t cooldown_duration_ms;

    std::chrono::time_point<std::chrono::steady_clock> timepoint;
};
