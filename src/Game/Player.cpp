#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//コンストラクタ
//  自機を原点・無回転・標準速度で初期化
Player::Player()
{
    moveSpeed = 20.0f;

    // モデルオフセットをy軸方向に-90度回転させ、正面を向かせる
    modelTransform.rotation.y = -90.0f;

    modelTransform.scale =
    {
        0.005f,
        0.005f,
        0.005f
    };
}

//更新
//  キー入力を受け取って位置と傾きを更新
void Player::update(GLFWwindow* window,float deltaTime)
{

    //デモ:ずっと前方へ移動する
    // transform.position.z -= moveSpeed * deltaTime;

    //入力
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        transform.position.y -= moveSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        transform.position.y += moveSpeed * deltaTime;

    //傾きの速度設定(1秒間でどれくらい傾くか)
    float bankSpeed = 120.0f;
    float maxBank = 20.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        transform.position.x -= moveSpeed * deltaTime;
        //左傾き
        transform.rotation.z += bankSpeed * deltaTime;
        if(transform.rotation.z > maxBank)
            transform.rotation.z = maxBank;

    }else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        transform.position.x += moveSpeed * deltaTime;
        //右傾き
        transform.rotation.z -= bankSpeed * deltaTime;
        if(transform.rotation.z < -maxBank)
            transform.rotation.z = -maxBank;

    }else{
        //キーを離すと0へ戻す
        transform.rotation.z *= std::pow(0.01f,deltaTime);

        //ほぼ0になったら完全に止める
        if(std::abs(transform.rotation.z) < 0.1f)
            transform.rotation.z = 0.0f;
    }
}