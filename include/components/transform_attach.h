#pragma once
#include <memory>
#include <vector>

#include "../helper/ecs.h"
#include "../helper/vec2d.h"

enum class AttachType
{
    ANCHRED, // does not move relative to attached object (they would have same trnasform)
    PIVOTING // can move relatively. (Transform needs to be reset by another system)
};

class TransformAttachComponent : public Component
{
public:
    TransformAttachComponent(Entity& a_entity,
                             Entity* a_attached_to_entity,
                             const Vec2D& position_offset,
                             double a_rotation_z_offset,
                             AttachType a_attach_type)
      : Component(a_entity)
      , attached_to_entity(a_attached_to_entity)
      , position_offset(position_offset)
      , rotation_z_offset(a_rotation_z_offset)
      , attach_type(a_attach_type){};

    Entity* attached_to_entity;

    Vec2D position_offset;
    double rotation_z_offset;

    AttachType attach_type;
};
