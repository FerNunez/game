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
    g_game_state.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (g_game_state.renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }

    /* Entities and components */
    // enemys
    std::shared_ptr<Entity> enemy = g_game_state.m_entity_manager.CreateEntity("Enemy");
    {
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*enemy, Vec2D(0, 0), Vec2D(0, 0));
        enemy->AddComponent(rigid_body);

        std::shared_ptr<TransformComponent> transform
          = std::make_shared<TransformComponent>(*enemy, Vec2D(320, 140), 0.0);
        enemy->AddComponent(transform);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(*enemy, true, 16, 16, Color(255, 255, 0));
        enemy->AddComponent(square_render);

        std::shared_ptr<CollidableComponent> collider
          = std::make_shared<CollidableComponent>(*enemy, true, 16, 16, CollisionGroup::ENEMY);
        enemy->AddComponent(collider);

        std::shared_ptr<HealthComponent> health
          = std::make_shared<HealthComponent>(*enemy, 100, 100);
        enemy->AddComponent(health);

        std::shared_ptr<DoDamageComponent> damage = std::make_shared<DoDamageComponent>(*enemy, 50);
        enemy->AddComponent(damage);

        entities.push_back(enemy);
    }

    // player
    std::shared_ptr<Entity> player = g_game_state.m_entity_manager.CreateEntity("player");
    {
        std::shared_ptr<PlayerComponent> player_comp = std::make_shared<PlayerComponent>(*player);
        player->AddComponent(player_comp);

        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*player, Vec2D(0, 0), Vec2D(0, 0));
        player->AddComponent(rigid_body);

        std::shared_ptr<TransformComponent> transform
          = std::make_shared<TransformComponent>(*player, Vec2D(250, 400), 0.0);
        player->AddComponent(transform);

        std::shared_ptr<HealthComponent> health
          = std::make_shared<HealthComponent>(*player, 1000, 1000);
        player->AddComponent(health);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(*player, true, 16, 16, Color(0, 0, 255));
        player->AddComponent(square_render);

        std::shared_ptr<CollidableComponent> collider = std::make_shared<CollidableComponent>(
          *player, true, 16, 16, CollisionGroup::FRIEND, CollisionType::SAT);
        player->AddComponent(collider);

        std::shared_ptr<Skill1Component> skill_1
          = std::make_shared<Skill1Component>(*player, SkillType::FIRE, 2000);
        player->AddComponent(skill_1);

        std::shared_ptr<Skill2Component> skill_2
          = std::make_shared<Skill2Component>(*player, SkillType::ICE, 500);
        player->AddComponent(skill_2);

        std::shared_ptr<Skill3Component> skill_3
          = std::make_shared<Skill3Component>(*player, SkillType::SWORD, 100);
        player->AddComponent(skill_3);

        std::shared_ptr<EnemySpawnerComponent> enemy_spawner
          = std::make_shared<EnemySpawnerComponent>(*player, 0, 10000);
        player->AddComponent(enemy_spawner);

        entities.push_back(player);
    }

    // SYSTEMS UPDATE
    std::shared_ptr<PlayerBehaviorSystem> player_behavior_system
      = std::make_shared<PlayerBehaviorSystem>(&entities);

    std::shared_ptr<EnemySpawningSystem> enemy_spawning_system
      = std::make_shared<EnemySpawningSystem>(&entities);

    std::shared_ptr<AISystem> ai_behavior_system = std::make_shared<AISystem>(&entities);

    std::shared_ptr<SkillGeneratorSystem> skill_generator
      = std::make_shared<SkillGeneratorSystem>(&entities);
    std::shared_ptr<PhysicsSystem> physics_system = std::make_shared<PhysicsSystem>(&entities);

    std::shared_ptr<CollisionSystem> collision_system
      = std::make_shared<CollisionSystem>(&entities);

    std::shared_ptr<InvurelnabilityApplierSystem> invulnerability_applier
      = std::make_shared<InvurelnabilityApplierSystem>(&entities);

    std::shared_ptr<DamageGeneratorSystem> damage_generator_system
      = std::make_shared<DamageGeneratorSystem>(&entities);

    std::shared_ptr<HealthDamageSystem> health_damage_system
      = std::make_shared<HealthDamageSystem>(&entities);

    std::shared_ptr<DestroyAfterHitSystem> destroy_after_hit_system
      = std::make_shared<DestroyAfterHitSystem>(&entities);

    std::shared_ptr<DestroyByTimeSystem> destroy_by_time_system
      = std::make_shared<DestroyByTimeSystem>(&entities);

    std::shared_ptr<InvurelnabilityManagerSystem> invulnerability_manager
      = std::make_shared<InvurelnabilityManagerSystem>(&entities);
    std::shared_ptr<DestroySystem> destroy_system = std::make_shared<DestroySystem>(&entities);

    systems_update.push_back(player_behavior_system);
    systems_update.push_back(enemy_spawning_system);

    systems_update.push_back(ai_behavior_system);

    systems_update.push_back(skill_generator);
    systems_update.push_back(physics_system);
    systems_update.push_back(collision_system);
    systems_update.push_back(invulnerability_applier);

    systems_update.push_back(damage_generator_system);
    systems_update.push_back(health_damage_system);
    systems_update.push_back(destroy_after_hit_system);
    systems_update.push_back(destroy_by_time_system);

    systems_update.push_back(invulnerability_manager);

    systems_update.push_back(destroy_system);

    // SYSTEM RENDER
    std::shared_ptr<SquareRendererSystem> square_renderer_system
      = std::make_shared<SquareRendererSystem>(&entities);
    std::shared_ptr<SpriteRendererSystem> sprite_renderer_system
      = std::make_shared<SpriteRendererSystem>(&entities);

    systems_render.push_back(square_renderer_system);
    systems_render.push_back(sprite_renderer_system);

    // Clearer
    std::shared_ptr<CleanerSystem> clean_system = std::make_shared<CleanerSystem>(&entities);
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

    //    std::cout << "Game Updating" << std::endl;

    /* handle input */
    InputHandler::handleInput();

    /* Updating */
    for (auto& system : systems_update)
    {
        system->Update(1);
    }

    //    for (auto& entity : entities)
    //    {
    //        TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
    //        if (transform_component == nullptr)
    //        {
    //            continue;
    //        }
    //        std::cout << "x,y: " << transform_component->position << std::endl;

    //        ColliderComponent* collide_component = entity->GetComponent<ColliderComponent>();
    //        if (collide_component == nullptr)
    //        {
    //            continue;
    //        }
    //    }
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

    SDL_RenderClear(g_game_state.renderer);

    for (auto& system : systems_render)
    {
        system->Update(1);
    }

    SDL_RenderPresent(g_game_state.renderer);

    // Drawing 2D or 3D graphics
    // Displaying text
    // Applying visual effects
    // Updating the screen
    //    std::cout << "Game Rendering" << std::endl;
}
