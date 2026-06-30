#pragma once

#include "Core/CollisionEvent.h"

class ScoreSystem{
public:
    void OnCollision(const CollisionEvent& e);

    int GetScore() const;

    void Reset();

private:
    int score = 0;
};