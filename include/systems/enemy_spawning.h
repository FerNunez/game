#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class EnemySpawningSystem : public System
{
public:
    EnemySpawningSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {

        std::vector<std::shared_ptr<Entity>> to_add{};

        for (auto entity : *m_entities)
        {
            EnemySpawnerComponent* enemy_spawning_component
              = entity->GetComponent<EnemySpawnerComponent>();

            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();
            InvulnerabilityComponent* invulnerability_component
              = entity->GetComponent<InvulnerabilityComponent>();

            if (enemy_spawning_component == nullptr || transform_component == nullptr)
            {
                continue;
            }

            //
            if (std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::steady_clock::now() - enemy_spawning_component->last_spawn)
                  .count()
                > enemy_spawning_component->spawn_cooldown_duration_ms)
            {
                // Update timestamp
                enemy_spawning_component->last_spawn = std::chrono::steady_clock::now();

                for (int enemy_idx(0); enemy_idx < enemy_spawning_component->number_enemies;
                     enemy_idx++)
                {
                    std::shared_ptr<Entity> enemy
                      = g_game_state.m_entity_manager.CreateEntity("asd");

                    std::shared_ptr<RigidBodyComponent> enemy_rigid_body_component
                      = std::make_shared<RigidBodyComponent>(*enemy, Vec2D(0, 0), Vec2D(0, 0));
                    enemy->AddComponent(enemy_rigid_body_component);

                    std::shared_ptr<TransformComponent> enemy_transform_component
                      = std::make_shared<TransformComponent>(
                        *enemy, transform_component->position, 0.0);
                    enemy->AddComponent(enemy_transform_component);

                    std::shared_ptr<SquareRenderComponent> enemy_square_render_component
                      = std::make_shared<SquareRenderComponent>(
                        *enemy, true, 16, 16, Color(255, 255, 0));
                    enemy->AddComponent(enemy_square_render_component);

                    std::shared_ptr<CollidableComponent> enemy_collider_component
                      = std::make_shared<CollidableComponent>(
                        *enemy, true, 16, 16, CollisionGroup::ENEMY);
                    enemy->AddComponent(enemy_collider_component);

                    std::shared_ptr<HealthComponent> enemy_health_component
                      = std::make_shared<HealthComponent>(*enemy, 100, 100);
                    enemy->AddComponent(enemy_health_component);

                    std::shared_ptr<DoDamageComponent> enemy_damage_component
                      = std::make_shared<DoDamageComponent>(*enemy, 10);
                    enemy->AddComponent(enemy_damage_component);

                    std::shared_ptr<AIBehaviorComponent> enemy_ai_component
                      = std::make_shared<AIBehaviorComponent>(*enemy, AIBehaviorType::RANDOM);
                    enemy->AddComponent(enemy_ai_component);

                    //                    // Force invulnerability:
                    std::shared_ptr<InvulnerabilityComponent> enemy_invulnerability_component
                      = std::make_shared<InvulnerabilityComponent>(*enemy, 6000);
                    enemy->AddComponent(enemy_invulnerability_component);

                    // add new invulnerability
                    enemy_invulnerability_component->invulnerabilities_map.insert(
                      { entity->id(), std::chrono::steady_clock::now() });

                    // TODO: FIX this shit that I have to add invulnerability like this
                    if (invulnerability_component == nullptr)
                    {
                        std::shared_ptr<InvulnerabilityComponent>
                          invulnerability_component_shared_pr
                          = std::make_shared<InvulnerabilityComponent>(*entity, 1000);

                        entity->AddComponent(invulnerability_component_shared_pr);
                        invulnerability_component = invulnerability_component_shared_pr.get();
                    }
                    invulnerability_component->invulnerabilities_map.insert(
                      { enemy->id(), std::chrono::steady_clock::now() });

                    // pushing in vector im already looping.. to fix?? maybeget a fixed forsier?
                    to_add.push_back(enemy);
                }
            }
        }

        for (auto enemey_to_add : to_add)
        {
            m_entities->push_back(enemey_to_add);
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
