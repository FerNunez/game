#include "bezier_builder.h"
#include "../components/components.h"
#include "../game_state.h"
#include "bezier.h"

void BezierBuilder::generateCurveEnties(std::vector<std::shared_ptr<Entity>>& entity_output,
                                        int number_sengments,
                                        const vec2f& p0,
                                        const vec2f& p1,
                                        const vec2f& p2,
                                        const vec2f& p3)
{

    // generate trayectory
    std::vector<float> T = Bezier::computeT(number_sengments, TrajectoryVelocityType::LINEAL);
    Trajectory trajectory = Bezier::computeTrajectory(T, p0, p1, p2, p3);

    entity_output.push_back(
      BezierBuilder::createEntityCurvePoint(p0, vec2i(4, 4), Color(255, 0, 0)));
    entity_output.push_back(
      BezierBuilder::createEntityCurvePoint(p1, vec2i(4, 4), Color(255, 0, 0)));
    entity_output.push_back(
      BezierBuilder::createEntityCurvePoint(p2, vec2i(4, 4), Color(255, 0, 0)));
    entity_output.push_back(
      BezierBuilder::createEntityCurvePoint(p3, vec2i(4, 4), Color(255, 0, 0)));

    for (int i(0); i < trajectory.points.size(); i++)
    {
        auto point = trajectory.points[i];
        //        auto tangents_vector = trajectory.tangents_vector[i];
        //        auto perpendicular_vector = trajectory.perpendicular_vector[i];

        std::shared_ptr<Entity> entity_point
          = BezierBuilder::createEntityCurvePoint(point, vec2i(2, 2), Color(0, 255, 0));
        entity_output.push_back(entity_point);
    }
}
std::shared_ptr<Entity> BezierBuilder::createEntityCurvePoint(const vec2f& point,
                                                              const vec2i& size,
                                                              const Color& color)
{
    std::shared_ptr<Entity> entity_point = g_game_state.m_entity_manager.CreateEntity("Ancres");

    std::shared_ptr<TransformComponent> transform
      = std::make_shared<TransformComponent>(*entity_point, Vec2D(point.x, point.y), 0.0);
    entity_point->AddComponent(transform);

    std::shared_ptr<SquareRenderComponent> square_render
      = std::make_shared<SquareRenderComponent>(*entity_point, true, size.x, size.y, color);

    entity_point->AddComponent(square_render);

    return entity_point;
}

void BezierBuilder::createEntityTrajectory(std::vector<std::shared_ptr<Entity>>& entity_output,
                                           const Trajectory& trajectory,
                                           const vec2i& size,
                                           const Color& color)
{
    for (int i(0); i < trajectory.points.size(); i++)
    {
        auto point = trajectory.points[i];
        //        auto tangents_vector = trajectory.tangents_vector[i];
        //        auto perpendicular_vector = trajectory.perpendicular_vector[i];

        std::shared_ptr<Entity> entity_point
          = BezierBuilder::createEntityCurvePoint(point, vec2i(2, 2), Color(0, 255, 0));
        entity_output.push_back(entity_point);
    }
}
