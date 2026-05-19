#pragma once

#include "Bullet.h"
#include "ObjectPool.h"

#include <glad/glad.h>

//====================================================================
//BulletManagerクラス
//
//  画面上に存在するすべての弾の一元管理を行う
//  弾の生成・更新・描画をまとめて行う
//  main.cppからはfire()/update()/draw()の3メソッドを呼ぶだけ
//
//  内部ではObjectPoolを用いて、固定長配列で弾を管理
//      heapアロケーションを避けることで、フレームごとの処理を安定にする
//      (ゲームループ中でnew/deleteを呼ばない)
//=====================================================================
class BulletManager{
public:
    //同時に存在できる弾の最大数を指定
    //  ObjectPoolのサイズを決める唯一の定数
    //  超過した場合、alloc()でnullptrを返し、発射が無視される
    static const int MAX_BULLETS = 256;

    //弾のオブジェクトプールを生成
    //  起動時にBullet*MAX_BULLETS個分のメモリをまとめて管理
    //  以後は確保済の要素の貸出/返却を行う
    ObjectPool<Bullet,MAX_BULLETS> bullets;

public:
    //弾を1発分生成して、初期化を行う
    //  プールに空きがない場合、何もしない
    //  @param pos  発射位置
    //  @param dir  速度ベクトル(方向*速度)
    void fire(
        glm::vec3 pos,
        glm::vec3 dir
    );

    //更新
    //  アクティブ状隊の弾をすべて更新
    //  毎フレームのゲームループから呼ぶ
    //  @param deltaTime    前フレームからの経過時間(秒)
    void update(float deltaTime);

    //描画
    //  update()の後、同フレーム内で呼ぶことを想定
    //  @pram modelLoc  シェーダの"model"uniformのロケーション
    //  @pram vao       弾の描画に用いる立方体のvao
    void draw(
        GLuint modelLoc,
        GLuint vao
    );
};