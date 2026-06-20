cmake_minimum_required(VERSION 3.16)
project(vampire_survivors_ufpi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(vampire_survivors
    src/main.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/Input.cpp
    src/Camera.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Projectile.cpp
    src/Weapon.cpp
    src/Collision.cpp
    src/WaveManager.cpp
    src/Texture.cpp
    src/Audio.cpp
    src/HUD.cpp
)

target_include_directories(vampire_survivors PRIVATE
    src
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

if(TARGET OpenGL::GL)
    target_link_libraries(vampire_survivors PRIVATE OpenGL::GL)
else()
    target_link_libraries(vampire_survivors PRIVATE ${OPENGL_gl_LIBRARY})
endif()

if(TARGET OpenGL::GLU)
    target_link_libraries(vampire_survivors PRIVATE OpenGL::GLU)
elseif(OPENGL_glu_LIBRARY)
    target_link_libraries(vampire_survivors PRIVATE ${OPENGL_glu_LIBRARY})
endif()

if(TARGET GLUT::GLUT)
    target_link_libraries(vampire_survivors PRIVATE GLUT::GLUT)
else()
    target_link_libraries(vampire_survivors PRIVATE ${GLUT_LIBRARIES})
endif()

if(MSVC)
    target_compile_options(vampire_survivors PRIVATE /W4)
else()
    target_compile_options(vampire_survivors PRIVATE -Wall -Wextra -Wpedantic)
endif()
