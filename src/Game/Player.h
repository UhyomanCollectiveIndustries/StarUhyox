#pragma once

#include "../Core/GameObject.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

//=====================================================
// Playerクラス
//
//  プレイヤーが操作する自機の状態管理と描画を担う
//
//  描画形状は三角形1枚のシンプルなモデル(今のところ)
//  左右移動時にbankAngleを付け、旋回を演出
//=====================================================
class Player : public GameObject{
public:

    //1フレームあたりの移動速度
    float moveSpeed;

public:
    //コンストラクタ
    Player();

    //更新
    //  キー入力を受け取り、位置と傾きを更新する
    //  毎フレームのゲームループ先頭で呼ぶ
    //  @param window キー状隊を取得するGLFWウィンドウ
    void update(GLFWwindow* window,float deltaTime);

    //描画
    //  自機のレンダリング
    //  @param modelLoc     シェーダの"model"ロケーション
    //  @param vao          自機用のvao
    void draw(GLuint modelLoc,GLuint vao);
};