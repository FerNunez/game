#pragma once
#include "vec2d.h"

bool Collide(const Vec2D& a_position_a,
             double a_width_a,
             double a_height_a,
             const Vec2D& a_position_b,
             double a_width_b,
             double a_height_b)
{
    if ((a_position_a.x + a_width_a / 2 > a_position_b.x - a_width_b / 2)
        && (a_position_a.x - a_width_a / 2 < a_position_b.x + a_width_b / 2)
        && (a_position_a.y + a_height_a / 2 > a_position_b.y - a_height_b / 2)
        && (a_position_a.y - a_height_a / 2 < a_position_b.y + a_height_b / 2))
    {
        return true;
    }

    return false;
}
