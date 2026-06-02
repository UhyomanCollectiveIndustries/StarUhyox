#pragma once

#include <glm/glm.hpp>

struct Explosion
{
    //アクティブ状態
    bool isActive = false;

    //位置
    glm::vec3 position;

    //寿命
    float lifeTime = 0.0f;
};