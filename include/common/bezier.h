#pragma once
#include "../helper/vector2d.h"
#include <vector>

enum class TrajectoryVelocityType
{
    LINEAL,
    QUADRATIC,          // x^2
    QUADRATIC_INVERSAL, // -x^2
    CUBIC
};

struct TrajectoryPoint
{
    TrajectoryPoint()
      : points(vec2f())
      , tangents_vector(vec2f())
      , perpendicular_vector(vec2f())

    {
    }
    vec2f points;
    vec2f tangents_vector;
    vec2f perpendicular_vector;
};

typedef std::vector<TrajectoryPoint> Trajectory;

class Bezier
{
public:
    Bezier(){};

    static Trajectory computeTrajectory(const std::vector<float>& T,
                                        const vec2f& p0,
                                        const vec2f& p1,
                                        const vec2f& p2,
                                        const vec2f& p3);

    static std::vector<float> computeT(int number_sengments,
                                       const TrajectoryVelocityType& a_trayectory_velicity);
};
