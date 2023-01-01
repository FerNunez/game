#pragma once

#include "../helper/ecs.h"
#include "../helper/vec2d.h"
#include <SDL2/SDL.h>

enum class SkillType
{
    FIRE,
    ICE,
    LIGHT,
    WIND,
    _NUM_SKILL_TYPE
};

enum class SkillEffect
{
    BURN,
    FROZEN,
    STUNT,
    KNOCKBACK,
    _NUM_SKILL_EFFECT
};

struct FireSkill
{
    double damage = 10;
    //	SkillEffect effect;
};

struct IceSkill
{
    double damage = 7;
    /*	SkillEffect effect*/;
};

class SkillGenerator
{
public:
    static std::shared_ptr<Entity> generateSkill(SkillType a_skill_effect, const Vec2D& origin);
};
