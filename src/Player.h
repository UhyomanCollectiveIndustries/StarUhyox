#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Player{
public:
    //位置
    glm::vec3 position;
    //回転
    glm::vec3 rotation;

    //自機の傾き
    float bankAngle;

    //移動速度
    float moveSpeed;

    //コンストラクタ
    Player();

    //更新
    void Update(GLFWwindow* window);
};