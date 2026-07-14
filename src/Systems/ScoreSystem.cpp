#include "ScoreSystem.h"

#include <iostream>

void ScoreSystem::OnCollision(
    const CollisionEvent& e)
{
    // score += 100;
}

void ScoreSystem::AddScore(int amount)
{
    score += amount;
}

int ScoreSystem::GetScore()const
{
    return score;
}