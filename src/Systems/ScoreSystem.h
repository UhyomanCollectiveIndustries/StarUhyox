#pragma once

#include "Core/CollisionEvent.h"

/**
 * スコア管理クラス
 * 
 * 衝突イベントを受け取り、スコアを加算する
 */
class ScoreSystem{
public:
    /**
     * 衝突イベントを受け取る
     * 
     * @param e 衝突イベント
     */
    void OnCollision(const CollisionEvent& e);

    /**
     * スコアの加算
     */
    void AddScore(int amount);

    /**
     * スコアを取得(ゲッター)
     */
    int GetScore() const;

    /**
     * スコアをリセット(0にする)
     */
    void Reset();

private:
    /**
     * スコア(初期値は0)
     */
    int score = 0;
};