#pragma once

#include "Explosion.h"

#include <array>
#include <glad/glad.h>

class ExplosionManager{
public:

    static constexpr int MAX_EXPLOSIONS = 64;

    std::array<
        Explosion,
        MAX_EXPLOSIONS
    >explosions;

public:

    //出現
    void spawn(const glm::vec3 posiotion);

    //更新
    void update(float deltaTIme);

    //描画
    void draw(GLuint modelLoc,GLuint vao);

};