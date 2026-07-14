#include "DestroySystem.h"

#include "../Game/Bullet.h"
#include "../Game/Stage.h"

DestroySystem::DestroySystem(ScoreSystem& scoreSystem):scoreSystem(scoreSystem)
{

}


// 衝突
void DestroySystem::OnCollision(
    const CollisionEvent& e
){
    // 弾を無効化
    e.bullet -> isActive = false;

    /**
     * 衝突したステージオブジェクトについて
     *  衝突フラグを有効化
     *  衝突後の演出のためのタイマー時間の設定
     */
    e.StageObject -> isHit = true;
    e.StageObject -> hitEffectTimer = 0.05f;

    scoreSystem.AddScore(100);
}