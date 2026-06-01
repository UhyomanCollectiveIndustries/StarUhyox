#include "SoundSystem.h"

#include <iostream>

//衝突
void SoundSystem::OnCollision(
    const CollisionEvent& e
)
{
    //デモ:ウィンドウにBOOMと出力
    std::cout << "BOOM!" << std::endl;
}