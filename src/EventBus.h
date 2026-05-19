#pragma once

#include "CollisionEvent.h"

#include <vector>
#include <functional>

//===================================
// EventBusクラス
//
//  各イベントとイベントキューの仲介
//====================================
class EventBus{
public:
    std::vector<
        std::function<void(const CollisionEvent&)>
    > collisionListeners;

public:
    //イベントの登録
    void subscribeCollision(
        std::function<void(const CollisionEvent&)> listener
    );

    //イベントの発行
    void publish(
        const CollisionEvent& e
    );
};