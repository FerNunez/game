#pragma once

#include "../helper/color.h"
#include "../helper/ecs.h"
#include "../helper/vector2d.h"

struct Trajectory;

class BezierBuilder
{
public:
    BezierBuilder(){};
    static void generateCurveEnties(std::vector<std::shared_ptr<Entity>>& entity_output,
                                    int number_sengments,
                                    const vec2f& p0,
                                    const vec2f& p1,
                                    const vec2f& p2,
                                    const vec2f& p3);

    static std::shared_ptr<Entity> createEntityCurvePoint(const vec2f& point,
                                                          const vec2i& size,
                                                          const Color& color);

    static void createEntityTrajectory(std::vector<std::shared_ptr<Entity>>& entity_output,
                                       const Trajectory& trajectory,
                                       const vec2i& size,
                                       const Color& color);
};
