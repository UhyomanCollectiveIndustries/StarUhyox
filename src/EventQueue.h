#pragma once

#include "CollisionEvent.h"

#include <vector>


//=====================================
// EventQueueクラス
//=====================================
class EventQueue{
public:
    //衝突イベントキュー
    std::vector<CollisionEvent>
        collisionEvent;

public:
    //全てのイベントキューをクリアする
    void Clear();
};