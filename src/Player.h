#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Player{
public:
    //コンストラクタ
    Player();

    //更新
    void Update(GLFWwindow* window);

    //描画
    void Draw(GLuint modelLoc,GLuint vao);

    //位置
    glm::vec3 position;
    //回転
    glm::vec3 rotation;

    //自機の傾き
    float bankAngle;

    //移動速度
    float moveSpeed;
};