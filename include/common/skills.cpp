#include "skills.h"
#include "../components/components.h"
#include "../game_state.h"

std::shared_ptr<Entity> SkillGenerator::generateSkill(SkillType a_skill_effect, const Vec2D& origin)
{
    std::shared_ptr<Entity> projectil = g_game_state.m_entity_manager.CreateEntity("Projectil");

    std::shared_ptr<TransformComponent> transform
      = std::make_shared<TransformComponent>(*projectil, Vec2D(origin.x, origin.y), 0.0);
    projectil->AddComponent(transform);

    switch (a_skill_effect)
    {
    case SkillType::FIRE:
    {
        Vec2D direction
          = Vec2D(g_game_state.skill_mouse_position_x, g_game_state.skill_mouse_position_y)
            - Vec2D(origin.x, origin.y);
        Vec2D direction_norm = direction.normalize();
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*projectil, direction_norm * 5, Vec2D(0, 0));
        projectil->AddComponent(rigid_body);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(*projectil, true, 16, 16, Color(255, 0, 0));
        projectil->AddComponent(square_render);

        // TODO: PASS COLLISION GROUP FROM ENTITY THAT  GENERATES THE SKILL?
        std::shared_ptr<CollidableComponent> collider
          = std::make_shared<CollidableComponent>(*projectil, true, 16, 16, CollisionGroup::FRIEND);
        projectil->AddComponent(collider);
        std::shared_ptr<DoDamageComponent> damage
          = std::make_shared<DoDamageComponent>(*projectil, 10);
        projectil->AddComponent(damage);
        std::shared_ptr<DestroyableAfterHitComponent> destroy_after_hit
          = std::make_shared<DestroyableAfterHitComponent>(*projectil, 30);
        projectil->AddComponent(destroy_after_hit);

        break;
    }
    case SkillType::ICE:
    {
        Vec2D direction
          = Vec2D(g_game_state.skill_mouse_position_x, g_game_state.skill_mouse_position_y)
            - Vec2D(origin.x, origin.y);
        Vec2D direction_norm = direction.normalize();
        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*projectil, direction_norm * 7.5, Vec2D(0, 0));
        projectil->AddComponent(rigid_body);

        std::shared_ptr<SquareRenderComponent> square_render
          = std::make_shared<SquareRenderComponent>(*projectil, true, 16, 16, Color(0, 255, 255));
        projectil->AddComponent(square_render);

        // TODO: PASS COLLISION GROUP FROM ENTITY THAT  GENERATES THE SKILL?
        std::shared_ptr<CollidableComponent> collider
          = std::make_shared<CollidableComponent>(*projectil, true, 16, 16, CollisionGroup::FRIEND);
        projectil->AddComponent(collider);
        std::shared_ptr<DoDamageComponent> damage
          = std::make_shared<DoDamageComponent>(*projectil, 100);
        projectil->AddComponent(damage);
        std::shared_ptr<DestroyableAfterHitComponent> destroy_after_hit
          = std::make_shared<DestroyableAfterHitComponent>(*projectil, 1);
        projectil->AddComponent(destroy_after_hit);
        break;
    }
    case SkillType::SWORD:
    {
        Vec2D direction
          = Vec2D(g_game_state.skill_mouse_position_x, g_game_state.skill_mouse_position_y)
            - Vec2D(origin.x, origin.y);
        Vec2D direction_norm = direction.normalize();

        /*+ direction_norm * Vec2D(31, 15);*/

        std::shared_ptr<RigidBodyComponent> rigid_body
          = std::make_shared<RigidBodyComponent>(*projectil, Vec2D(0, 0), Vec2D(0, 0));
        projectil->AddComponent(rigid_body);

        //        std::shared_ptr<SquareRenderComponent> squere_render
        //          = std::make_shared<SquareRenderComponent>(*projectil, true, 24, 32, Color(100,
        //          100, 100));
        //        projectil->AddComponent(squere_render);

        std::shared_ptr<SpriteRenderComponent> sprite_render
          = std::make_shared<SpriteRenderComponent>(
            *projectil, true, "../assets/pink_square.png", 16, 16, Vec2D(4, 1));
        projectil->AddComponent(sprite_render);

        // TODO: PASS COLLISION GROUP FROM ENTITY THAT  GENERATES THE SKILL?
        std::shared_ptr<CollidableComponent> collider = std::make_shared<CollidableComponent>(
          *projectil, true, 16 * 4, 16, CollisionGroup::FRIEND);
        projectil->AddComponent(collider);
        std::shared_ptr<DoDamageComponent> damage
          = std::make_shared<DoDamageComponent>(*projectil, 50);
        projectil->AddComponent(damage);
        std::shared_ptr<DestroyableByTimeComponent> destroy_by_time
          = std::make_shared<DestroyableByTimeComponent>(*projectil, 100);
        projectil->AddComponent(destroy_by_time);

        // desplacement
        auto angle_rad = std::atan2(direction_norm.y, direction_norm.x);
        auto deplacement = (sprite_render->width * sprite_render->scale.x / 2);
        transform->rotation_z = angle_rad * 180.0 / 3.1415926535;
        transform->position.x = transform->position.x + cos(angle_rad) * deplacement;
        transform->position.y = transform->position.y + sin(angle_rad) * deplacement;
        break;
    }
    default:
    {
        break;
    }
    }

    return projectil;
}
