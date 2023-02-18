#pragma once
#include <SDL2/SDL.h>
#include <chrono>
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../game_state.h"
#include "../helper/ecs.h"
#include "../helper/vec2d.h"
#include "../common/state_machine.h"

class AnimatorSystem : public System
{
public:
    AnimatorSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            AnimationComponent* animation_component = entity->GetComponent<AnimationComponent>();
            SpriteRenderComponent* sprite_renderer = entity->GetComponent<SpriteRenderComponent>();
            StateComponent* state_component = entity->GetComponent<StateComponent>();

            if (animation_component == nullptr)
            {
                continue;
            }
            if (sprite_renderer == nullptr)
            {
                continue;
            }

            if (state_component == nullptr)
            {
                continue;
            }

            // get corresponding animation
            StateDirectionPair state_direction_pair(state_component->current_state,
                                                    state_component->facing_direction);

            if (animation_component->statedirection_to_animation_type_to_map.find(
                  state_direction_pair)
                != animation_component->statedirection_to_animation_type_to_map.end())
            {

                AnimationType& animation_type
                  = animation_component
                      ->statedirection_to_animation_type_to_map[state_direction_pair];

                if (animation_component->animation_type_to_animation_map.find(animation_type)
                    != animation_component->animation_type_to_animation_map.end())
                {
                    auto& animation_data
                      = animation_component->animation_type_to_animation_map.at(animation_type);

                    // if new animation, reset counter
                    if (animation_component->last_animation_type != animation_type)
                    {
                        animation_component->last_animation_type = animation_type;
                        animation_component->current_animation_index = 0;
                        animation_component->animation_time_start
                          = std::chrono::steady_clock::now();
                    }

                    // change rect source
                    sprite_renderer->rect_src.x
                      = sprite_renderer->width * animation_component->current_animation_index;
                    sprite_renderer->rect_src.y
                      = sprite_renderer->height * animation_data.column_index;
                    sprite_renderer->rect_src.w = sprite_renderer->width;
                    sprite_renderer->rect_src.h = sprite_renderer->height;

                    // flip
                    sprite_renderer->flip
                      = (state_component->facing_direction == FacingDirection::LEFT) ? true : false;
                    // prepare for next frame animation
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::steady_clock::now()
                          - animation_component->animation_time_start)
                          .count()
                        > animation_data.frame_duration_ms)
                    {
                        animation_component->current_animation_index++;

                        animation_component->animation_time_start
                          = std::chrono::steady_clock::now();

                        if(animation_component->current_animation_index>= animation_data.number_frames)
                        {
                            animation_component->current_animation_index = 0;
                            StateMachine::endState(state_component->state_behavior, state_component->current_state);
                        }

                    }
                }
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
