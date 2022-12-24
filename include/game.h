#pragma once
#include "game_state.h"

#include <SDL2/SDL.h>
#include <memory>

#include "components/components.h"
#include "helper/ecs.h"

class Game
{
public:
    Game(SDL_Window* a_window);
    ~Game();

    inline bool getIsRunning()
    {
        return m_is_running;
    }

    void Update();

    void Render();

    SDL_Window* window;
    SDL_Renderer* renderer = nullptr;

private:
    bool m_is_running;

    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<System>> systems_update;

    std::vector<std::shared_ptr<System>> systems_render;
};
