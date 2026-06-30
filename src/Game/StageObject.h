#pragma once

#include "../Core/GameObject.h"

struct StageObject : public GameObject
{
public:
    /** 当たり判定の半径 */
    float radius = 5.0f;

    /** アクティブフラグ */
    bool isActive = true;
};