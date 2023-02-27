#pragma once
#include <memory>
#include <vector>

#include "../components/components.h"
#include "../helper/ecs.h"

class TrajectoryFollowerSystem : public System
{
public:
    TrajectoryFollowerSystem(std::vector<std::shared_ptr<Entity>>* entities)
      : m_entities(entities){};

    void Update(double dt) override
    {
        for (auto entity : *m_entities)
        {
            TrajectoryFollowComponent* trajectory_follow_component
              = entity->GetComponent<TrajectoryFollowComponent>();
            TransformComponent* transform_component = entity->GetComponent<TransformComponent>();

            if (trajectory_follow_component == nullptr)
            {
                continue;
            }
            if (transform_component == nullptr)
            {
                continue;
            }

            std::uint64_t time_step = trajectory_follow_component->duration_ms
                                      / trajectory_follow_component->trajetory_size;

            auto time_passed_ms
              = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::steady_clock::now() - trajectory_follow_component->init_time)
                  .count();
            if (time_passed_ms < trajectory_follow_component->duration_ms)
            {
                float step_duration = static_cast<float>(trajectory_follow_component->duration_ms)
                                      / trajectory_follow_component->trajetory_size;

                std::uint64_t idx = static_cast<std::uint64_t>(time_passed_ms / step_duration);

                transform_component->position.x
                  = trajectory_follow_component->trajectory[idx].points.x;
                transform_component->position.y
                  = trajectory_follow_component->trajectory[idx].points.y;

                transform_component->rotation_z
                  = atan2(trajectory_follow_component->trajectory[idx].tangents_vector.y,
                          trajectory_follow_component->trajectory[idx].tangents_vector.x);
            }
            else
            {
                auto last_element_idx = trajectory_follow_component->trajectory.size() - 1;
                transform_component->position.x
                  = trajectory_follow_component->trajectory[last_element_idx].points.x;
                transform_component->position.y
                  = trajectory_follow_component->trajectory[last_element_idx].points.y;

                transform_component->rotation_z = atan2(
                  trajectory_follow_component->trajectory[last_element_idx].tangents_vector.y,
                  trajectory_follow_component->trajectory[last_element_idx].tangents_vector.x);
            }
        }
    }

private:
    std::vector<std::shared_ptr<Entity>>* m_entities;
};
