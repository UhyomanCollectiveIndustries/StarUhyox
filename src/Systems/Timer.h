#pragma once

class Timer
{
public:
    /** 
     * タイマーの初期化
     * 残り時間に最大時間をセット
     * 終了フラグをfalseに
     */
    void start(float seconds);

    /**
     * タイマー更新
     */
    void update(float deltaTime);

    /**
     * 終了したかどうかを取得
     */
    bool isFinishing() const;

    /**
     * 残り時間を取得
     * UI表示用などに使用
     */
    float getRemainingTime() const;

private:
    /** 残り時間 */
    float remainingTime = 0.0f;

    /** 終了フラグ */
    bool finished = false;
};