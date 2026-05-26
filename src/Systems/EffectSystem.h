#pragma once

#include "../Core/CollisionEvent.h"
#include "../Effects/ExplosionManager.h"

class EffectSystem
{
public:

    ExplosionManager* explosionManager;

public:

    //コンストラクタ
    EffectSystem(ExplosionManager* manager);

    //衝突イベント
    void OnCollision(const CollisionEvent& e);

};
