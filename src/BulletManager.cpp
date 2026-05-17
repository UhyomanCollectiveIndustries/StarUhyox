#include "BulletManager.h"

void BulletManager::fire(glm::vec3 pos,glm::vec3 dir){
    Bullet* b =  bullets.alloc();
    if(!b) return;
    
    b->init(pos,dir);
}

void BulletManager::update(float deltaTime){
    bullets.forEachActive(
        [&](Bullet& b){
            b.update(deltaTime);
        }
    );
}

void BulletManager::draw(GLuint modelLoc,GLuint vao){
    bullets.forEachActive(
        [&](Bullet& b){
            b.draw(modelLoc,vao);
        }
    );
}