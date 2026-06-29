#include "GameStateManager.h"

void GameStateManager::changeState(GameState state)
{
    currentState = state;
}


GameState GameStateManager::GetState() const
{
    return currentState;
}