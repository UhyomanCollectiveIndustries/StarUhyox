#include "Timer.h"

void Timer::start(float seconds)
{
    remainingTime = seconds;
    finished = false;
}

void Timer::update(float deltaTime)
{
    if(finished)
        return;

    remainingTime -= deltaTime;

    // 残り時間が0以下になったら終了フラグをtrueに
    if(remainingTime <= 0.0f)
    {
        remainingTime = 0.0f;
        finished = true;
    }
}

bool Timer::isFinishing() const
{
    return finished;
}