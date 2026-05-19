#pragma once

#include "COllisionEvent.h"

#include <vector>


//=====================================
// EventQueueクラス
//=====================================
class EventQueue{
public:
    //衝突イベントキュー
    std::vector<CollisonEvent>
        collisionEvent;

public:
    //全てのイベントキューをクリアする
    void Clear();
};