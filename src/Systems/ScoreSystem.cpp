#include "ScoreSystem.h"

#include <iostream>

void ScoreSystem::OnCollision(
    const CollisionEvent& e)
{
    score += 100;
    std::cout << score << std::endl;
}