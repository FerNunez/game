#include "bezier.h"

Trajectory Bezier::computeTrajectory(const std::vector<float>& T,
                                     const vec2f& p0,
                                     const vec2f& p1,
                                     const vec2f& p2,
                                     const vec2f& p3)
{
    //  curve: [x,y]= (1–t)^3*P0 + 3*(1–t)^2*t*P1 + 3*(1–t)*t^2*P2 + t^3*P3
    //
    Trajectory bezier_trajectory;
    for (auto& t : T)
    {
        float u = 1 - t;
        float uu = u * u;
        float uuu = uu * u;

        float tt = t * t;
        float ttt = tt * t;

        vec2f p = uuu * p0;
        p = p + (3 * uu * t) * p1;
        p = p + (3 * u * tt) * p2;
        p = p + (ttt * p3);

        TrajectoryPoint tp;
        tp.points = p;

        vec2f p_dot = (-3 * tt + 6 * t - 3) * p0;
        p_dot = p_dot + (9 * tt - 12 * t + 3) * p1;
        p_dot = p_dot + (-9 * tt + 6 * t) * p2;
        p_dot = p_dot + (3 * tt) * p3;

        tp.tangents_vector = p_dot;
        tp.perpendicular_vector = perpendicularVector(p_dot);

        bezier_trajectory.push_back(tp);
    }

    return bezier_trajectory;
}

std::vector<float> Bezier::computeT(int number_sengments,
                                    const TrajectoryVelocityType& a_trayectory_velicity)

{
    std::vector<float> T;
    float acum = 0;
    float acm = 0;
    switch (a_trayectory_velicity)
    {

    case TrajectoryVelocityType::LINEAL:
        for (int i(0); i < number_sengments + 1; i++)
        {
            float x = static_cast<float>(i) / number_sengments;
            T.push_back(x);
        }
        break;
    case TrajectoryVelocityType::QUADRATIC:
        for (int i(0); i < number_sengments + 1; i++)
        {
            float x = (static_cast<float>(i - 1) / number_sengments);
            T.push_back(x * x);
        }
        break;
    case TrajectoryVelocityType::CUBIC:
        while (T.size() <= number_sengments)
        {

            float x = (acum - 0.5) * (acum - 0.5) / (0.5 * 0.5);
            acum += 1.0f / number_sengments;
            T.push_back(x);
            std::cout << "x: " << x << std::endl;
        }
        for (auto el : T)
        {
            acm += el;
        }
        for (auto& el : T)
        {
            el /= acm * 1 / number_sengments;
            std::cout << "el: " << el << std::endl;
        }

        break;
    default:

        break;
    }
    return T;
}
