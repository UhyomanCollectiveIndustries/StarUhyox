cmake_minimum_required(VERSION 3.10)
project(StarUhyox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#====================================
# OpenGL
#====================================
find_package(OpenGL REQUIRED)

#====================================
# GLFW
#====================================
add_library(glad STATIC
    libs/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    libs/glad/include
)

#=====================================
# SoLoud
#=====================================
file(GLOB SOLOUD_SOURCES
    "libs/soloud/src/core/*.cpp"
    "libs/soloud/src/backend/winmm/*.cpp"

    #WAV読み込み
    "libs/soloud/src/audiosource/wav/*.cpp"
    "libs/soloud/src/audiosource/wav/*.c"

    #stb_vorbies読み込み
    "libs/soloud/src/audiosource/wav/stb_vorbis.c"
)

add_library(soloud STATIC
    ${SOLOUD_SOURCES}
)

target_include_directories(soloud PUBLIC
    libs/soloud/include
)

target_compile_definitions(soloud PRIVATE
    WITH_WINMM
)


#=======================================
# Assimp
#=======================================
add_subdirectory(libs/assimp)

#=======================================
# 実行ファイル
#=======================================
file(GLOB_RECURSE GAME_SOURCES
    src/*.cpp
    src/Core/Transform.cpp
)

add_executable(StarUhyox
    ${GAME_SOURCES}
)

#========================================
# Include
#========================================
target_include_directories(StarUhyox PRIVATE
    libs
    libs/glad/include
    libs/glfw/include
    libs/soloud/include
    libs/assimp/include

    src
)

#========================================
# Link
#========================================
target_link_libraries(StarUhyox PRIVATE

    glad
    soloud
    assimp

    ${CMAKE_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib

    OpenGL::GL
    winmm
)

#========================================
# Assimp DLLコピー
#========================================
add_custom_command(
    TARGET StarUhyox POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:assimp>
    $<TARGET_FILE_DIR:StarUhyox>
)

#========================================
# Assets コピー
#========================================
add_custom_command(
    TARGET StarUhyox POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:StarUhyox>/assets
)

# UTF-8フラグを追加
target_compile_options(StarUhyox PRIVATE /utf-8)