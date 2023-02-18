#pragma once
#include <memory>
#include <vector>

#include "../common/skills.h"
#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"
#include "../common/state_machine.h"


class SkillGeneratorSystem : public System
{
public:
    SkillGeneratorSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            if (entity == nullptr)
            {
                continue;
            }
            Skill1Component* skill1_component = entity->GetComponent<Skill1Component>();
            Skill2Component* skill2_component = entity->GetComponent<Skill2Component>();
            Skill3Component* skill3_component = entity->GetComponent<Skill3Component>();
            StateComponent* state_component = entity->GetComponent<StateComponent>();

            if (skill1_component == nullptr && skill2_component == nullptr
                && skill3_component == nullptr)
            {
                continue;
            }

            if (skill1_component != nullptr)
            {
                auto time_since_last_skill_ms
                  = std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::steady_clock::now() - skill1_component->last_call_timepoint)
                      .count();
                if (g_game_state.skill_1
                    && time_since_last_skill_ms >= skill1_component->cooldown_duration_ms)
                {
                    skill1_component->last_call_timepoint = std::chrono::steady_clock::now();

                    TransformComponent* transform_component
                      = entity->GetComponent<TransformComponent>();
                    std::shared_ptr<Entity> projectil = SkillGenerator::generateSkill(
                      skill1_component->skill_type, transform_component->position);
                    m_entities->push_back(projectil);
                }
            }

            if (skill2_component != nullptr)
            {
                auto time_since_last_skill_ms
                  = std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::steady_clock::now() - skill2_component->last_call_timepoint)
                      .count();
                if (g_game_state.skill_2
                    && time_since_last_skill_ms >= skill2_component->cooldown_duration_ms)
                {
                    skill2_component->last_call_timepoint = std::chrono::steady_clock::now();

                    TransformComponent* transform_component
                      = entity->GetComponent<TransformComponent>();
                    std::shared_ptr<Entity> projectil = SkillGenerator::generateSkill(
                      skill2_component->skill_type, transform_component->position);
                    m_entities->push_back(projectil);
                }
            }

            if (skill3_component != nullptr)
            {
                auto time_since_last_skill_ms
                  = std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::steady_clock::now() - skill3_component->last_call_timepoint)
                      .count();
                if (g_game_state.skill_3
                    && time_since_last_skill_ms >= skill3_component->cooldown_duration_ms)
                {
                    skill3_component->last_call_timepoint = std::chrono::steady_clock::now();

                    TransformComponent* transform_component
                      = entity->GetComponent<TransformComponent>();
                    std::shared_ptr<Entity> projectil = SkillGenerator::generateSkill(
                      skill3_component->skill_type, transform_component->position);
                    m_entities->push_back(projectil);
                    StateMachine::enterState(state_component->state_behavior, state_component->current_state, State::ATTACK);
                }
            }

            // CreateSkill
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
