#include "skills.h"
#include "../components/components.h"
#include "../game_state.h"

std::shared_ptr<Entity> SkillGenerator::generateSkill(SkillType a_skill_effect, const Vec2D& origin)
{

    std::shared_ptr<Entity> projectil = std::make_shared<Entity>(10, "Projectil");

    {
        std::shared_ptr<TransformComponent> transform = std::make_shared<TransformComponent>(
          *projectil, Vec2D(origin.x, origin.y), Vec2D(0, 0), Vec2D(0, 0));
        projectil->AddComponent(transform);
    }

    switch (a_skill_effect)
    {
    case SkillType::FIRE:
    {
        Vec2D direction
          = Vec2D(g_game_state.skill_mouse_position_x, g_game_state.skill_mouse_position_y)
            - Vec2D(origin.x, origin.y);
        Vec2D direction_norm = direction.normalize();
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*projectil, direction_norm, Vec2D(0, 0));
        projectil->AddComponent(rigid_body);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(*projectil, true, 16, 16, Color(255, 0, 0));
        projectil->AddComponent(square_render);

        // TODO: PASS COLLISION GROUP FROM ENTITY THAT  GENERATES THE SKILL?
        std::shared_ptr<ColliderComponent> collider
          = std::make_shared<ColliderComponent>(*projectil, true, 16, 16, CollisionGroup::FRIEND);
        projectil->AddComponent(collider);
        std::shared_ptr<DoDamageComponent> damage
          = std::make_shared<DoDamageComponent>(*projectil, 10);
        projectil->AddComponent(damage);
        break;
    }
    case SkillType::ICE:
    {
        Vec2D direction
          = Vec2D(g_game_state.skill_mouse_position_x, g_game_state.skill_mouse_position_y)
            - Vec2D(origin.x, origin.y);
        Vec2D direction_norm = direction.normalize();
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*projectil, direction_norm * 1.5, Vec2D(0, 0));
        projectil->AddComponent(rigid_body);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(*projectil, true, 16, 16, Color(0, 255, 255));
        projectil->AddComponent(square_render);

        // TODO: PASS COLLISION GROUP FROM ENTITY THAT  GENERATES THE SKILL?
        std::shared_ptr<ColliderComponent> collider
          = std::make_shared<ColliderComponent>(*projectil, true, 16, 16, CollisionGroup::FRIEND);
        projectil->AddComponent(collider);
        std::shared_ptr<DoDamageComponent> damage
          = std::make_shared<DoDamageComponent>(*projectil, 10);
        projectil->AddComponent(damage);
        break;
    }
    default:
    {
        break;
    }
    }

    return projectil;
}
