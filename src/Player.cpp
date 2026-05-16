#include "Player.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//コンストラクタ
Player::Player(){
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    bankAngle = 0.0f;

    moveSpeed = 0.05f;
}

//更新
void Player::Update(GLFWwindow* window){
    //入力
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position.y -= moveSpeed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position.y += moveSpeed;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        position.x -= moveSpeed;
        //左傾き
        bankAngle = 20.0f;
    }else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        position.x += moveSpeed;
        //右傾き
        bankAngle = -20.0f;
    }else{
        bankAngle *= 0.9f;
    }
}

//描画
void Player::Draw(GLuint modelLoc){
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        position
    );

    model = glm::rotate(
        model,
        glm::radians(bankAngle),
        glm::vec3(0.0f,0.0f,1.0f)
    );

    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    glDrawArrays(GL_TRIANGLES,0,36);
}