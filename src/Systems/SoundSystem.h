#pragma once

#include "../Core/CollisionEvent.h"

class SoundSystem
{
public:
    //衝突
    // 衝突イベントを検知したときに発火
    // @param e 衝突イベント
    void OnCollision(
        const CollisionEvent& e
    );
};