#include "Player.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//コンストラクタ
//  自機を原点・無回転・標準速度で初期化
Player::Player(){
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    bankAngle = 0.0f;

    moveSpeed = 20.0f;
}

//更新
//  キー入力を受け取って位置と傾きを更新
void Player::update(GLFWwindow* window,float deltaTime){

    //デモ:ずっと前方へ移動する
    position.z -= moveSpeed * deltaTime;

    //入力
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position.y -= moveSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position.y += moveSpeed * deltaTime;

    //傾きの速度設定(1秒間でどれくらい傾くか)
    float bankSpeed = 120.0f;
    float maxBank = 20.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        position.x -= moveSpeed * deltaTime;
        //左傾き
        bankAngle += bankSpeed * deltaTime;
        if(bankAngle > maxBank) bankAngle = maxBank;

    }else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        position.x += moveSpeed * deltaTime;
        //右傾き
        bankAngle -= bankSpeed * deltaTime;
        if(bankAngle < -maxBank) bankAngle = -maxBank;

    }else{
        //キーを離すと0へ戻す
        bankAngle *= std::pow(0.01f,deltaTime);

        //ほぼ0になったら完全に止める
        if(std::abs(bankAngle) < 0.1f) bankAngle = 0.0f;
    }
}

//描画
//  デモ:自機を三角形としてレンダリング
//  将来的にはまた別のモデルを使う
void Player::draw(GLuint modelLoc,GLuint vao){
    glm::mat4 model = glm::mat4(1.0f);

    //ワールド座標に移動
    model = glm::translate(
        model,
        position
    );

    //バンク角をz軸回転で適応
    model = glm::rotate(
        model,
        glm::radians(bankAngle),
        glm::vec3(0.0f,0.0f,1.0f)
    );

    //計算したモデル行列をシェーダに送る
    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    //Playerの頂点データを更新
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES,0,3);
}