#pragma once

#include "../Core/GameObject.h"

class StageObject : public GameObject
{
public:
    /** 当たり判定の半径 */
    float radius = 1.0f;

    /** アクティブフラグ */
    bool isActive = true;

    // /** 更新 */
    // void update(float deltaTime) override;
};