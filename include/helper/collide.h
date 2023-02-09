#pragma once
#include "../components/components.h"
#include "vec2d.h"

std::vector<Vec2D> getVertex(const Vec2D& a_center_position,
                             double rotation,
                             double width,
                             double height)
{
    std::vector<Vec2D> vertex;

    // Rotation
    //   q2 | q1
    //  ----------
    //   q3 | q4
    //
    // x = x_original * cos(rotation) - y_original * sin(rotation)
    // y= x_original * sin(rotation) + y_original * cos(rotation)

    std::vector<double> vec_x = { width / 2, -width / 2, -width / 2, width / 2 };
    std::vector<double> vec_y = { height / 2, height / 2, -height / 2, -height / 2 };

    for (size_t idx(0); idx < vec_x.size(); idx++)
    {
        vertex.push_back(a_center_position
                         + Vec2D(vec_x[idx] * cos(rotation) - vec_y[idx] * sin(rotation),
                                 (vec_x[idx] * sin(rotation) + vec_y[idx] * cos(rotation))));
    }

    return vertex;
}

bool Collide(const CollisionType& a_collision_type,
             TransformComponent* a_transform_a,
             double a_width_a,
             double a_height_a,
             TransformComponent* a_transform_b,
             double a_width_b,
             double a_height_b)
{

    switch (a_collision_type)
    {
    case CollisionType::AABB:
    {
        if ((a_transform_a->position.x + a_width_a / 2 > a_transform_b->position.x - a_width_b / 2)
            && (a_transform_a->position.x - a_width_a / 2
                < a_transform_b->position.x + a_width_b / 2)
            && (a_transform_a->position.y + a_height_a / 2
                > a_transform_b->position.y - a_height_b / 2)
            && (a_transform_a->position.y - a_height_a / 2
                < a_transform_b->position.y + a_height_b / 2))
        {
            return true;
        }
        break;
    }
    // do ast
    case CollisionType::SAT:
    {
        std::vector<Vec2D> vertex_a
          = getVertex(a_transform_a->position, a_transform_a->rotation_z, a_width_a, a_height_a);

        std::vector<Vec2D> vertex_b
          = getVertex(a_transform_b->position, a_transform_b->rotation_z, a_width_b, a_height_b);

        // LOOP FOR A
        for (int idx(0); idx < vertex_a.size(); idx++)
        {

            Vec2D va1 = vertex_a[idx];
            Vec2D va2 = vertex_a[(idx + 1) % vertex_a.size()];

            Vec2D perpendicular = (va1 - va2).perpendicular();

            double min_projection_a = std::numeric_limits<double>::max();
            double max_projection_a = std::numeric_limits<double>::lowest();

            double min_projection_b = std::numeric_limits<double>::max();
            double max_projection_b = std::numeric_limits<double>::lowest();
            // Loop and project all my vertex
            for (auto ver_a : vertex_a)
            {
                auto projection = perpendicular.dot(ver_a);

                if (projection <= min_projection_a)
                {
                    min_projection_a = projection;
                }

                if (projection >= max_projection_a)
                {
                    max_projection_a = projection;
                }
            }

            // Loop and project all enemy vertex
            for (auto ver_b : vertex_b)
            {
                auto projection = perpendicular.dot(ver_b);

                if (projection <= min_projection_b)
                {
                    min_projection_b = projection;
                }

                if (projection >= max_projection_b)
                {
                    max_projection_b = projection;
                }
            }

            // Check if there is a gap on projection => if there is, no collission
            if ((max_projection_a < max_projection_b && max_projection_a < min_projection_b)
                || (max_projection_b < max_projection_a && max_projection_b < min_projection_a))
            {
                return false;
            }
        }

        // LOOP FOR B
        for (int idx(0); idx < vertex_b.size(); idx++)
        {
            Vec2D vb1 = vertex_b[idx];
            Vec2D vb2 = vertex_b[(idx + 1) % vertex_b.size()];

            Vec2D perpendicular = (vb1 - vb2).perpendicular();

            double min_projection_a = std::numeric_limits<double>::max();
            double max_projection_a = std::numeric_limits<double>::lowest();

            double min_projection_b = std::numeric_limits<double>::max();
            double max_projection_b = std::numeric_limits<double>::lowest();

            // Loop and project all my vertex
            for (auto ver_b : vertex_b)
            {
                auto projection = perpendicular.dot(ver_b);

                if (projection <= min_projection_b)
                {
                    min_projection_b = projection;
                }

                if (projection >= max_projection_b)
                {
                    max_projection_b = projection;
                }
            }

            // Loop and project all enemy vertex
            for (auto ver_a : vertex_a)
            {
                auto projection = perpendicular.dot(ver_a);

                if (projection <= min_projection_a)
                {
                    min_projection_a = projection;
                }

                if (projection >= max_projection_a)
                {
                    max_projection_a = projection;
                }
            }

            // Check if there is a gap on projection => if there is, no collission
            if ((max_projection_a < max_projection_b && max_projection_a < min_projection_b)
                || (max_projection_b < max_projection_a && max_projection_b < min_projection_a))
            {
                return false;
            }
        }
        // no gap => Collision detected
        return true;
        break;
    }
    default:
        break;
    }

    return false;
}
