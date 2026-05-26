#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

//=====================================================
// Playerクラス
//
//  プレイヤーが操作する自機の状態管理と描画を担う
//
//  描画形状は三角形1枚のシンプルなモデル(今のところ)
//  左右移動時にbankAngleを付け、旋回を演出
//=====================================================
class Player{
public:
    //ワールド座標の現在位置
    //  BulletManager::fire()にも渡されるため、publicに
    glm::vec3 position;

    //各軸の回転軸
    //  現在は未使用
    glm::vec3 rotation;

    //自機の傾き
    //  左右入力時のz軸回転角度
    float bankAngle;

    //1フレームあたりの移動速度
    float moveSpeed;

public:
    //コンストラクタ
    Player();

    //更新
    //  キー入力を受け取り、位置と傾きを更新する
    //  毎フレームのゲームループ先頭で呼ぶ
    //  @param window キー状隊を取得するGLFWウィンドウ
    void update(GLFWwindow* window);

    //描画
    //  自機のレンダリング
    //  @param modelLoc     シェーダの"model"ロケーション
    //  @param vao          自機用のvao
    void draw(GLuint modelLoc,GLuint vao);
};