#include "DestroySystem.h"

#include "../Game/Bullet.h"
#include "../Game/Stage.h"

//衝突
void DestroySystem::OnCollision(
    const CollisionEvent& e
){
    //弾を無効化
    e.bullet -> isActive = false;

    //衝突したステージオブジェクトを無効化
    e.StageObject -> isActive = false;
}