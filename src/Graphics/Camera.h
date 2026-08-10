#pragma once

#include "../Core/GameObject.h"

#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public GameObject{
public:
    // コンストラクタ
    Camera();

    // カメラの前方向(どこをみるか)
    glm::vec3 target;

    glm::mat4 GetViewMatrix();
};