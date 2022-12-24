#include <SDL.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "include/game.h"
#include "include/game_state.h"

const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;

// global Game State
GameState g_game_state;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("My Game",               // window title
                                          SDL_WINDOWPOS_UNDEFINED, // initial x position
                                          SDL_WINDOWPOS_UNDEFINED, // initial y position
                                          640,                     // width, in pixels
                                          480,                     // height, in pixels
                                          SDL_WINDOW_OPENGL        // flags - see below
    );

    Game game(window);

    while (game.getIsRunning())
    {
        auto start_time_point = std::chrono::steady_clock::now();

        // game->Update game state
        game.Update();

        // game->Render frame
        game.Render();

        // Delay to achieve a frame rate of at least 60 fps
        auto elapsed_time_duration = std::chrono::steady_clock::now() - start_time_point;

        if (elapsed_time_duration < std::chrono::milliseconds(FRAME_DELAY))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY)
                                        - elapsed_time_duration);
        }

        auto loop_time_duration = std::chrono::steady_clock::now() - start_time_point;
        std::cout
          << "FPS: "
          << 1000.0
               / std::chrono::duration_cast<std::chrono::milliseconds>(loop_time_duration).count()
          << std::endl;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
