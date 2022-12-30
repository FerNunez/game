cmake_minimum_required(VERSION 3.16)
project(MyProject)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Add the source files
set(SOURCES
  main.cpp
  src/game.cpp
  src/input_handler.cpp
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



  include/components/components.h
  include/components/transform.h
  include/components/rigid_body.h
  include/components/player.h
  include/components/square_render.h
  include/components/collider.h
  include/components/health.h
  include/components/damage.h
  include/components/shield.h
  
  include/systems/systems.h
  include/systems/physics.h
  include/systems/player_behavior.h
  include/systems/renderer.h
  include/systems/collision.h
  include/systems/clean.h

)

# Add the executable
add_executable(MyProject ${SOURCES} ${INCLUDES})

# Add any library dependencies
#target_link_libraries(MyProject mylib1 mylib2)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})