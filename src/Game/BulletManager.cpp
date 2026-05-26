#include "BulletManager.h"

//弾を一発分生成し、指定の位置・方向で初期化
void BulletManager::fire(glm::vec3 pos,glm::vec3 dir){
    Bullet* b =  bullets.alloc();
    if(!b) return;
    
    b->init(pos,dir);
}

//アクティブな弾を全て更新
void BulletManager::update(float deltaTime){
    bullets.forEachActive(
        [&](Bullet& b){
            b.update(deltaTime);
        }
    );
}

//アクティブな弾を全て描画
void BulletManager::draw(GLuint modelLoc,GLuint vao){
    bullets.forEachActive(
        [&](Bullet& b){
            b.draw(modelLoc,vao);
        }
    );
}