#include "../include/input_handler.h"
#include "../include/game_state.h"

#include "SDL.h"

void InputHandler::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // KeyDown
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                g_game_state.move_left = 1;
                break;
            case SDLK_d:
                g_game_state.move_right = 1;
                break;
            case SDLK_z:
                g_game_state.move_up = 1;
                break;
            case SDLK_s:
                g_game_state.move_down = 1;
                break;

            case SDLK_1:
                g_game_state.skill_1 = 1;
                SDL_GetMouseState(&g_game_state.skill_mouse_position_x,
                                  &g_game_state.skill_mouse_position_y);
                break;
            case SDLK_2:
                g_game_state.skill_2 = 1;
                SDL_GetMouseState(&g_game_state.skill_mouse_position_x,
                                  &g_game_state.skill_mouse_position_y);
                break;
            case SDLK_3:
                g_game_state.skill_3 = 1;
                SDL_GetMouseState(&g_game_state.skill_mouse_position_x,
                                  &g_game_state.skill_mouse_position_y);
                break;
            case SDLK_4:
                g_game_state.skill_4 = 1;
                SDL_GetMouseState(&g_game_state.skill_mouse_position_x,
                                  &g_game_state.skill_mouse_position_y);
                break;
            case SDL_QUIT:
            case SDLK_ESCAPE:
                g_game_state.exit = 1;
                break;
            default:
                break;
            }
            break;
        // KeyUP
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                g_game_state.move_left = 0;
                break;
            case SDLK_d:
                g_game_state.move_right = 0;
                break;
            case SDLK_z:
                g_game_state.move_up = 0;
                break;
            case SDLK_s:
                g_game_state.move_down = 0;
                break;
            case SDLK_1:
                g_game_state.skill_1 = 0;
                break;
            case SDLK_2:
                g_game_state.skill_2 = 0;
                break;
            case SDLK_3:
                g_game_state.skill_3 = 0;
                break;
            case SDLK_4:
                g_game_state.skill_4 = 0;
                break;

            case SDL_QUIT:
            case SDLK_ESCAPE:
                g_game_state.exit = 0;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}
