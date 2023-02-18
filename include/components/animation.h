#pragma once
#include <chrono>
#include <map>
#include <utility>

#include "../common/state_machine.h"
#include "../helper/ecs.h"

typedef std::pair<State, FacingDirection> StateDirectionPair;

struct Animation
{
    Animation(int a_column_index, int a_number_frames)
      : column_index(a_column_index)
      , number_frames(a_number_frames)
    {
        frame_duration_ms = 100;
    }
    Animation(int a_column_index, int a_number_frames, std::uint32_t a_frame_duration_ms)
      : column_index(a_column_index)
      , number_frames(a_number_frames)
      , frame_duration_ms(a_frame_duration_ms)
    {
    }

    int column_index;
    int number_frames;
    std::uint32_t frame_duration_ms;
};

enum class AnimationType
{
    IDLE_DOWN,
    IDLE_SIDE,
    IDLE_UP,
    WALK_DOWN,
    WALK_SIDE,
    WALK_UP,
    ATTACK_DOWN,
    ATTACK_SIDE,
    ATTACK_UP,
    DEATH
};

class AnimationComponent : public Component
{
public:
    AnimationComponent(Entity& a_entity)
      : Component(a_entity)
      , animation_time_start(std::chrono::steady_clock::now())
    {

        current_animation_index = 0;

        // TODO: READ FROM JSON
        // idle
        animation_type_to_animation_map.insert({ AnimationType::IDLE_DOWN, Animation(0, 6) });
        animation_type_to_animation_map.insert({ AnimationType::IDLE_SIDE, Animation(1, 6) });
        animation_type_to_animation_map.insert({ AnimationType::IDLE_UP, Animation(2, 6) });
        // walk
        animation_type_to_animation_map.insert({ AnimationType::WALK_DOWN, Animation(3, 6) });
        animation_type_to_animation_map.insert({ AnimationType::WALK_SIDE, Animation(4, 6) });
        animation_type_to_animation_map.insert({ AnimationType::WALK_UP, Animation(5, 6) });

        // attack
        animation_type_to_animation_map.insert({ AnimationType::ATTACK_DOWN, Animation(9, 4) });
        animation_type_to_animation_map.insert({ AnimationType::ATTACK_SIDE, Animation(10, 4) });
        animation_type_to_animation_map.insert({ AnimationType::ATTACK_UP, Animation(11, 4) });

        // Death
        animation_type_to_animation_map.insert({ AnimationType::DEATH, Animation(9, 3) });

        // State - Direction to AnimationType
        statedirection_to_animation_type_to_map.insert(
          { { State::IDLE, FacingDirection::DOWN }, AnimationType::IDLE_DOWN });
        statedirection_to_animation_type_to_map.insert(
          { { State::IDLE, FacingDirection::UP }, AnimationType::IDLE_UP });
        statedirection_to_animation_type_to_map.insert(
          { { State::IDLE, FacingDirection::LEFT }, AnimationType::IDLE_SIDE });
        statedirection_to_animation_type_to_map.insert(
          { { State::IDLE, FacingDirection::RIGHT }, AnimationType::IDLE_SIDE });

        statedirection_to_animation_type_to_map.insert(
          { { State::WALK, FacingDirection::DOWN }, AnimationType::WALK_DOWN });
        statedirection_to_animation_type_to_map.insert(
          { { State::WALK, FacingDirection::UP }, AnimationType::WALK_UP });
        statedirection_to_animation_type_to_map.insert(
          { { State::WALK, FacingDirection::LEFT }, AnimationType::WALK_SIDE });
        statedirection_to_animation_type_to_map.insert(
          { { State::WALK, FacingDirection::RIGHT }, AnimationType::WALK_SIDE });

        statedirection_to_animation_type_to_map.insert(
          { { State::ATTACK, FacingDirection::DOWN }, AnimationType::ATTACK_DOWN });
        statedirection_to_animation_type_to_map.insert(
          { { State::ATTACK, FacingDirection::UP }, AnimationType::ATTACK_UP });
        statedirection_to_animation_type_to_map.insert(
          { { State::ATTACK, FacingDirection::LEFT }, AnimationType::ATTACK_SIDE });
        statedirection_to_animation_type_to_map.insert(
          { { State::ATTACK, FacingDirection::RIGHT }, AnimationType::ATTACK_SIDE });

        statedirection_to_animation_type_to_map.insert(
          { { State::DEATH, FacingDirection::NONE }, AnimationType::DEATH });
    }

    int current_animation_index;

    std::chrono::time_point<std::chrono::steady_clock> animation_time_start;

    AnimationType last_animation_type;

    std::map<AnimationType, Animation> animation_type_to_animation_map;
    std::map<StateDirectionPair, AnimationType> statedirection_to_animation_type_to_map;
};
