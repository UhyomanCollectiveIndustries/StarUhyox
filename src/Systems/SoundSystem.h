#pragma once

#include "../Core/CollisionEvent.h"

class SoundSystem
{
public:

    void OnCollision(
        const CollisionEvent& e
    );
};