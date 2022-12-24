#pragma once
#include "helper/vec2d.h"

struct GameState
{

    bool exit = 0;

    // Arrows
    bool move_left = 0;
    bool move_right = 0;
    bool move_up = 0;
    bool move_down = 0;

    //    // Mouse Position
    int skill_mouse_position_x = 0;
    int skill_mouse_position_y = 0;

    // Skill
    bool skill_1 = 0;
    bool skill_2 = 0;
    bool skill_3 = 0;
    bool skill_4 = 0;

    bool velocity_constant = 1;
};

extern GameState g_game_state;
