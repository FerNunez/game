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

  include/components/components.h
  include/components/transform.h
  include/components/rigid_body.h
  include/components/player.h
  include/components/square_render.h
  include/components/collidable.h
  include/components/collided.h
  include/components/health.h
  include/components/do_damage.h
  include/components/suffer_damage.h
  include/components/destroyable_after_hit.h
  include/components/invulnerability.h



  include/components/shield.h
  include/components/skill1.h
  include/components/skill2.h
  include/components/skill3.h
  include/components/skill4.h

  include/systems/systems.h
  include/systems/physics.h
  include/systems/player_behavior.h
  include/systems/renderer.h
  include/systems/collision.h
  include/systems/invulnerability_applier.h
  include/systems/invulnerability_manager.h

  include/systems/skill_generator.h
  include/systems/destroy.h
  include/systems/damage_generator.h
  include/systems/health_damage.h
  include/systems/destroy_after_hit.h


  include/systems/clean.h

)

# Add the executable
add_executable(MyProject ${SOURCES} ${INCLUDES})

# Add any library dependencies
#target_link_libraries(MyProject mylib1 mylib2)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})