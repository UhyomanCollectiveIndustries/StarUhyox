#pragma once

#include "RenderContext.h"
#include "Game/Player.h"
#include "Game/BulletManager.h"
#include "Game/Stage.h"
#include "Effects/ExplosionManager.h"
#include "Graphics/Camera.h"

/** 
 * ステート描画クラス 
 * ステートに応じての描画を管理する
 */
class StateRenderer
{
public:
    
    /** タイトルの描画 */
    void DrawTitle(const RenderContext& context);

    /** ゲームの描画 */
    void DrawPlaying(
        Camera& camera,
        Player& player,
        BulletManager& bulletManager,
        Stage& stage,
        ExplosionManager& explosionManager,
        const RenderContext& context
    );

    /** ゲームオーバの描画 */
    void DrawGameOver(const RenderContext& context);
};