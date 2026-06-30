#pragma once

#include "Game/Player.h"
#include "Game/BulletManager.h"
#include "Game/Stage.h"
#include "Graphics/Camera.h"
#include "Effects/ExplosionManager.h"
#include "Systems/CollisionManager.h"
#include "Core/EventQueue.h"
#include "Core/EventBus.h"
#include "Game/GameStateManager.h"
#include "Systems/Timer.h"

/**
 * ステートごとの更新処理を管理するクラス
 */
class StateUpdater
{
public:
    /** タイトルステートの更新 */
    void updateTitle(
        GLFWwindow* window,
        float deltaTime,
        GameStateManager& gameStateManager,
        Timer& timer
    );

    /** プレイングステートの更新 */
    void updatePlaying(
        GLFWwindow* window,
        float deltaTime,
        Camera& camera,
        Player& player,
        BulletManager& bulletManager,
        Stage& stage,
        ExplosionManager& explosionManager,
        CollisionManager& collisionManager,
        EventQueue& eventQueue,
        EventBus& eventBus
    );

    /** ゲームオーバステートの更新 */
    void updateGameOver(
        GLFWwindow* window,
        float deltaTime,
        GameStateManager& gameStateManager
    );

};