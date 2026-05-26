#include "DestroySystem.h"

#include "../Game/Bullet.h"
#include "../Game/Stage.h"

void DestroySystem::OnCollision(
    const CollisionEvent& e
){
    //弾を無効化
    e.bullet -> isActive = false;

    //ステージオブジェクトを無効化
    e.StageObject -> isActive = false;
}