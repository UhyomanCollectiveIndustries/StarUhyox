#include "SoundSystem.h"

#include <iostream>

void SoundSystem::OnCollision(
    const CollisionEvent& e
)
{
    std::cout << "BOOM!" << std::endl;
}