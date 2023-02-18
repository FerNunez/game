cmake_minimum_required(VERSION 3.16)
project(MyProject)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Add the source files
set(SOURCES
  main.cpp
  src/game.cpp
  src/input_handler.cpp

  include/common/skills.cpp
  include/common/AI.cpp
  
  include/common/state_machine.cpp  
)

# Add the include files
set(INCLUDES
  include/game_state.h
  include/game.h
  include/input_handler.h
  
  include/helper/vec2d.h
  include/helper/ecs.h  
  include/helper/color.h  
  include/helper/collide.h  

  include/common/skills.h
  include/common/AI.h
  include/common/state_machine.h

  include/components/components.h
  include/components/transform.h
  include/components/rigid_body.h
  include/components/player.h

  include/components/animation.h
  include/components/square_render.h
  include/components/sprite_render.h

  include/components/collidable.h
  include/components/collided.h
  include/components/health.h
  include/components/do_damage.h
  include/components/suffer_damage.h
  include/components/destroyable_after_hit.h
  include/components/invulnerability.h
  include/components/enemy_spawner.h
  include/components/destroyable_by_time.h

  include/components/state.h


  include/components/shield.h
  include/components/skill1.h
  include/components/skill2.h
  include/components/skill3.h
  include/components/skill4.h

  include/systems/systems.h
  include/systems/physics.h
  include/systems/player_behavior.h
  include/systems/animator.h
  include/systems/square_renderer.h
  include/systems/sprite_renderer.h

  include/systems/collision.h
  include/systems/invulnerability_applier.h
  include/systems/invulnerability_manager.h
  include/systems/enemy_spawning.h



  include/systems/skill_generator.h
  include/systems/destroy.h
  include/systems/damage_generator.h
  include/systems/health_damage.h
  include/systems/destroy_after_hit.h
  include/systems/destroying_by_time.h


  include/systems/clean.h

)

# Add the executable
add_executable(MyProject ${SOURCES} ${INCLUDES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
