#pragma once

#include "../Core/GameObject.h"

struct StageObject : public GameObject
{
public:
    /** 当たり判定の半径 */
    float radius = 5.0f;

    /** アクティブフラグ */
    bool isActive = true;

    /** 衝突フラグ */
    bool isHit = false;
    
    /** 衝突した後の演出用のタイマー
     *      ※この際の演出とはモデルに直接適応する演出です。
     *        (色を変更、大きさを変更、位置を変更させる、など)
     */
    float hitEffectTimer = 0.0f;

    /** コリジョンマネージャーでイベントを一度しか発生させないためのフラグ */
    bool collisionProcessed = false;
};