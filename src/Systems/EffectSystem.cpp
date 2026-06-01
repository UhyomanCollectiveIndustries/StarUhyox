#include "EffectSystem.h"
#include "../Game/Stage.h"


// コンストラクタ
EffectSystem::EffectSystem(ExplosionManager* manager){
    explosionManager = manager;
}

// 衝突イベント
// @param CoolllisionEvent
// 爆発マネージャーのspawnを呼ぶ
void EffectSystem::OnCollision(const CollisionEvent& e){
    explosionManager->spawn(
        e.StageObject->position
    );
}