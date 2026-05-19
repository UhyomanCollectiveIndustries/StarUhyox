#pragma once

#include "BulletManager.h"
#include "Stage.h"
#include "EventQueue.h"

//==========================================
//CollisionManagerクラス
//
//  ゲーム内オブジェクトの衝突判定を管理する
//==========================================
class CollisionManager{
public:

public:
    //弾とステージオブジェクトの衝突判定
    //  @param bullets  弾
    //  @param stage    ステージオブジェクト
    void checkBulletVsStage(
        BulletManager& bullets,
        Stage& stage,
        EventQueue& eventQueue
    );
};