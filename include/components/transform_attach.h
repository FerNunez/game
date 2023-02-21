#pragma once
#include <memory>
#include <vector>

#include "../helper/ecs.h"
#include "../helper/vec2d.h"

class TransformAttachComponent : public Component
{
public:
    TransformAttachComponent(
      Entity& a_entity,
      Entity* a_attached_to_entity,
      const Vec2D& position_offset,
      double a_rotation_z_offset,
      const Vec2D& position_relative, // position relative to attache to= cause by movement
      double a_rotation_z_relative)
      : Component(a_entity)
      , attached_to_entity(a_attached_to_entity)
      , position_offset(position_offset)
      , rotation_z_offset(a_rotation_z_offset)
      , position_relative(position_relative)
      , rotation_z_relative(a_rotation_z_relative){};

    enum AttachType
    {
        TRANSLATIONAL,
        ROTATIONAL,
        FULL
    };

    Entity* attached_to_entity;

    Vec2D position_offset;
    double rotation_z_offset;
    Vec2D position_relative;
    double rotation_z_relative;
    AttachType attach_type;
};
