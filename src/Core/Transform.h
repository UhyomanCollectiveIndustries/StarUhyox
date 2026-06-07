#pragma once

#include <glm/glm.hpp>

class Transform
{
public:

    //位置
    glm::vec3 position =
    {
        0.0f,
        0.0f,
        0.0f
    };

    //回転
    glm::vec3 rotation =
    {
        0.0f,
        0.0f,
        0.0f
    };

    //大きさ
    glm::vec3 scale =
    {
        1.0f,
        1.0f,
        1.0f
    };

    glm::mat4 GetMatrix() const;
};