#pragma once

#include "CollisionEvent.h"

//===========================
// DestroySystemクラス
//
//  破壊処理担当
//===========================
class DestroySystem{
public:

    void OnCollision(
        const CollisionEvent& e
    );
};