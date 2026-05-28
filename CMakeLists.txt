cmake_minimum_required(VERSION 3.10)
project(StarUhyox)

set(CMAKE_CXX_STANDARD 17)

# GLAD（ソースとして直接組み込む）
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# 実行ファイル
add_executable(StarUhyox 
    src/main.cpp
    src/Game/Player.cpp
    src/Graphics/Camera.cpp
    src/Game/Stage.cpp
    src/Game/Bullet.cpp
    src/Game/BulletManager.cpp
    src/Systems/CollisionManager.cpp
    src/Core/EventQueue.cpp
    src/Core/EventBus.cpp
    src/Systems/DestroySystem.cpp
    src/Systems/EffectSystem.cpp
    src/Effects/ExplosionManager.cpp
    src/Systems/SoundSystem.cpp
    )

# インクルードパス
target_include_directories(StarUhyox PRIVATE
    libs/glfw/include
    libs/glad/include
    libs
)

# ライブラリのリンク
target_link_libraries(StarUhyox
    glad
    ${CMAKE_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib
    opengl32
)

# UTF-8フラグを追加
target_compile_options(StarUhyox PRIVATE /utf-8)