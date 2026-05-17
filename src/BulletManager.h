#pragma once

#include "Bullet.h"
#include "ObjectPool.h"

#include <glad/glad.h>

class BulletManager{
public:
    //弾の最大数を指定
    static const int MAX_BULLETS = 256;

    //弾のオブジェクトプールを生成
    ObjectPool<Bullet,MAX_BULLETS> bullets;

public:
    //弾の発火
    void fire(
        glm::vec3 pos,
        glm::vec3 dir
    );

    //更新
    void update(float deltaTime);

    //描画
    void draw(
        GLuint modelLoc,
        GLuint vao
    );
};