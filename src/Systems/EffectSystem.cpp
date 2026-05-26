#include "EffectSystem.h"
#include "../Game/Stage.h"

EffectSystem::EffectSystem(ExplosionManager* manager){
    explosionManager = manager;
}

void EffectSystem::OnCollision(const CollisionEvent& e){
    explosionManager->spawn(
        e.StageObject->position
    );
}