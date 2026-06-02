cmake_minimum_required(VERSION 3.10)
project(StarUhyox)

set(CMAKE_CXX_STANDARD 17)

# GLAD（ソースとして直接組み込む）
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

#SoLoud(ソースとして直接読み込む)
file(GLOB SOLOUD_SOURCES
    "libs/soloud/src/core/*.cpp"
    "libs/soloud/src/backend/winmm/*.cpp"

    #WAV
    "libs/soloud/src/audiosource/wav/*.cpp"
    "libs/soloud/src/audiosource/wav/*.c"
)

add_library(soloud STATIC ${SOLOUD_SOURCES})

# SoLoudのビルドに必要なマクロ定義（Windowsの標準オーディオを使う指定）
target_compile_definitions(soloud PRIVATE WITH_WINMM)

# インクルードパスを通す
target_include_directories(soloud PUBLIC libs/soloud/include)

# 実行ファイル
add_executable(StarUhyox 
    src/main.cpp
    src/Game/Player.cpp
    src/Game/Stage.cpp
    src/Game/Bullet.cpp
    src/Game/BulletManager.cpp
    src/Graphics/Camera.cpp
    src/Core/EventQueue.cpp
    src/Core/EventBus.cpp
    src/Systems/CollisionManager.cpp
    src/Systems/DestroySystem.cpp
    src/Systems/EffectSystem.cpp 
    src/Systems/SoundSystem.cpp
    src/Effects/ExplosionManager.cpp
    )

# インクルードパス
target_include_directories(StarUhyox PRIVATE
    libs/glfw/include
    libs/glad/include
    libs/soloud/include
    libs
)

# ライブラリのリンク
target_link_libraries(StarUhyox
    glad
    soloud
    ${CMAKE_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib
    opengl32
    winmm
)

# UTF-8フラグを追加
target_compile_options(StarUhyox PRIVATE /utf-8)