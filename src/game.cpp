#include "../include/game.h"
#include "../include/game_state.h"
#include "../include/input_handler.h"

#include "../include/components/components.h"
#include "../include/systems/systems.h"

#include <SDL.h>
#include <iostream>

Game::Game(SDL_Window* a_window)
  : m_is_running(true)
  , window(a_window)
  , renderer(nullptr)
{
    /*Initialize member variables*/
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);
    }

    /* Entities and components */
    // enemys
    std::shared_ptr<Entity> enemy = std::make_shared<Entity>(1, "Enemy");
    {
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*enemy, Vec2D(0, 0), Vec2D(0, 0));
        enemy->AddComponent(rigid_body);

        std::shared_ptr<TransformComponent> transform
          = std::make_shared<TransformComponent>(*enemy, Vec2D(320, 140), Vec2D(0, 0), Vec2D(0, 0));
        enemy->AddComponent(transform);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(
            *enemy, renderer, true, 16, 16, Color(255, 0, 0));
        enemy->AddComponent(square_render);

        std::shared_ptr<ColliderComponent> collider
          = std::make_shared<ColliderComponent>(*enemy, true, 16, 16);
        enemy->AddComponent(collider);

        entities.push_back(enemy);
    }

    std::shared_ptr<Entity> enemy2 = std::make_shared<Entity>(2, "Enemy2");
    {
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*enemy2, Vec2D(0, 0), Vec2D(0, 0));
        enemy2->AddComponent(rigid_body);

        std::shared_ptr<TransformComponent> transform = std::make_shared<TransformComponent>(
          *enemy2, Vec2D(250, 140), Vec2D(0, 0), Vec2D(0, 0));
        enemy2->AddComponent(transform);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(
            *enemy2, renderer, true, 16, 16, Color(255, 0, 122));
        enemy2->AddComponent(square_render);

        std::shared_ptr<ColliderComponent> collider
          = std::make_shared<ColliderComponent>(*enemy2, true, 16, 16);
        enemy2->AddComponent(collider);

        entities.push_back(enemy2);
    }

    // player
    std::shared_ptr<Entity> player = std::make_shared<Entity>(0, "Ferni");
    {
        std::shared_ptr<PlayerComponent> player_comp = std::make_shared<PlayerComponent>(*player);
        player->AddComponent(player_comp);

        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*player, Vec2D(0, 0), Vec2D(0, 0));
        player->AddComponent(rigid_body);

        std::shared_ptr<TransformComponent> transform
          = std::make_shared<TransformComponent>(*player, Vec2D(0, 0), Vec2D(0, 0), Vec2D(0, 0));
        player->AddComponent(transform);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(
            *player, renderer, true, 16, 16, Color(0, 0, 255));
        player->AddComponent(square_render);

        std::shared_ptr<ColliderComponent> collider
          = std::make_shared<ColliderComponent>(*player, true, 16, 16);
        player->AddComponent(collider);

        entities.push_back(player);
    }

    // SYSTEMS UPDATE
    std::shared_ptr<PlayerBehaviorSystem> player_behavior_system
      = std::make_shared<PlayerBehaviorSystem>(entities);
    std::shared_ptr<PhysicsSystem> physics_system = std::make_shared<PhysicsSystem>(entities);
    std::shared_ptr<CollisionSystem> collision_system = std::make_shared<CollisionSystem>(entities);

    systems_update.push_back(player_behavior_system);
    systems_update.push_back(physics_system);
    systems_update.push_back(collision_system);

    // SYSTEM RENDER
    std::shared_ptr<RendererSystem> renderer_system = std::make_shared<RendererSystem>(entities);

    systems_render.push_back(renderer_system);

    // Clearer
    std::shared_ptr<CleanerSystem> clean_system = std::make_shared<CleanerSystem>(entities);
    systems_render.push_back(clean_system);
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    // Clean up resources
}

void Game::Update()
{
    if (g_game_state.exit)
    {
        m_is_running = false;
    }

    std::cout << "Game Updating" << std::endl;

    /* handle input */
    InputHandler::handleInput();

    std::cout << "Skill 1: " << g_game_state.skill_1 << std::endl;
    std::cout << "Skill 2: " << g_game_state.skill_2 << std::endl;
    std::cout << "Skill 3: " << g_game_state.skill_3 << std::endl;
    std::cout << "Skill 4: " << g_game_state.skill_4 << std::endl;

    std::cout << "Mouse position: (" << g_game_state.skill_mouse_position_x << ", "
              << g_game_state.skill_mouse_position_x << ")" << std::endl;
    /* Updating */
    for (auto& system : systems_update)
    {
        system->Update(1);
    }

    for (auto& entity : entities)
    {
        TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
        if (transform_component == nullptr)
        {
            continue;
        }
        std::cout << "x,y: " << transform_component->position << std::endl;

        ColliderComponent* collide_component = entity->GetComponent<ColliderComponent>();
        if (collide_component == nullptr)
        {
            continue;
        }
        if (collide_component->entities_collided_to.size())
        {
            for (auto entity_collided_to : collide_component->entities_collided_to)
            {
                std::cout << "Colliding: " << entity->name() << " with "
                          << entity_collided_to->name() << std::endl;
            }
        }
    }
    //
    // Handling user input
    // Updating the positions of game objects
    // Checking for collisions
    // Updating the game state
    // Performing AI calculations*
}
void Game::Render()
{
    //    SDL_RenderClear(renderer);
    //    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //    SDL_RenderPresent(renderer);

    SDL_RenderClear(renderer);

    for (auto& system : systems_render)
    {
        system->Update(1);
    }

    SDL_RenderPresent(renderer);

    // Drawing 2D or 3D graphics
    // Displaying text
    // Applying visual effects
    // Updating the screen
    std::cout << "Game Rendering" << std::endl;
}
