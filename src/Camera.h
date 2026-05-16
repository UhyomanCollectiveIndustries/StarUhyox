#pragma once

#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
    //コンストラクタ
    Camera();

    glm::mat4 GetViewMatrix();

    //カメラ位置
    glm::vec3 position;

    //カメラの前方向(どこをみるか)
    glm::vec3 target;

    //カメラの上方向
    glm::vec3 up;
};