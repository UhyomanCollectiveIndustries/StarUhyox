#pragma once

#include "Game/Player.h"
#include "Game/BulletManager.h"
#include "Game/Stage.h"
#include "Effects/ExplosionManager.h"
#include "Graphics/Camera.h"

struct RenderContext
{
    unsigned int shagerProgram;

    unsigned int modelLoc;
    unsigned int viewLoc;
    unsigned int projectionLoc;

    unsigned int colorLocation;

    unsigned int cubeVAO;
};


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