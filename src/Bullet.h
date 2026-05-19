#pragma once

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//=================================================================
//Bulletクラス
//
//  プレイヤーが発射する弾1発分のデータ、挙動を管理
//  ObjectPoolによって事前に確保されるため、動的メモリ確保は行わない
//  弾は「位置+速度ベクトル」のみで表現、物理演算をもたない
//==================================================================
class Bullet{
public:
    //現在のワールド座標
    glm::vec3 position;

    //1発あたりの移動量(方向と速度を兼ねたベクトル)
    //発射時に、fire()から渡され、以後変化しない
    glm::vec3 velocity;

    //使用中かどうかのフラグ
    bool isActive = false;

public:
    //初期化
    //  弾の指定の位置・方向で初期化、アクティブ状態にする
    //  ObjectPool::alloc()でスロットを確保した直後に呼ぶ
    //  @param startPos 発射起点(通常はプレイヤーの現在座標)
    //  @param dir      速度ベクトル(方向*速度)
    void init(
        glm::vec3 startPos,
        glm::vec3 dir
    );

    //更新
    //  弾の位置をdeltaTime分だけ進める
    //  毎フレームBulletManagerから呼ばれる
    //  @param deltaTime 前フレームからの経過時間(秒)
    void update(float deltaTime);

    //描画
    //  isActiveがfalseなら何もしない
    //  @param modelLoc シェーダの"model"uniformのロケーション
    //  @param vao      描画に用いる立方体のvao
    void draw(
        GLuint modelLoc,
        GLuint vao
    );
};