#pragma once

#include "../Core/CollisionEvent.h"
#include "../Systems/ScoreSystem.h"
#include "../Systems/SoundSystem.h"

//===========================
// DestroySystemクラス
//
//  破壊処理担当
//===========================
class DestroySystem{
public:

    // コンストラクタ
    DestroySystem(ScoreSystem& scoreSystem);

    // 衝突
    // 衝突イベントを検知したときに発火
    // @param e 衝突イベント
    void OnCollision(
        const CollisionEvent& e
    );

private:
    ScoreSystem& scoreSystem;
};