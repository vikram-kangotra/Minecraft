cmake_minimum_required(VERSION 3.10)

project(Minecraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/world.cpp
    src/shader.cpp
    src/game.cpp
    src/block/dirtBlock.cpp 
    src/block/mesh.cpp
    src/block/block.cpp
    src/block/skybox.cpp
    src/camera.cpp
    src/textureManager.cpp
)

add_executable(Minecraft ${SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_Image REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(Minecraft ${SDL2_LIBRARIES} SDL2_image::SDL2_image ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
