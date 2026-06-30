#include "StateRenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void StateRenderer::DrawTitle(const RenderContext& context)
{
    // カラーバッファのクリア
    glClearColor(0.0f,0.0f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void StateRenderer::DrawPlaying(
    Camera& camera,
    Player& player,
    BulletManager& bulletManager,
    Stage& stage,
    ExplosionManager& explosionManager,
    const RenderContext& context
)
{
    // カラーバッファのクリア
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //背景を青緑色に指定
    // 深度バッファのクリア
    //  クリアしないと、前フレームの深度値が残り、正しい前後関係が判定できない
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(context.shagerProgram);



    glm::mat4 view = camera.GetViewMatrix();

    // 透視投影行列:FOV 70°/アスペクト比:800:600/near=0.1,far=100
    //  FOVを広めにして、スピード感を演出
    glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    glUniformMatrix4fv(
        context.viewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(view)
    );
    glUniformMatrix4fv(
        context.projectionLoc,
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );


    //------------
    // Player描画
    //-----------
    glUniform4f(
        context.colorLocation,
        0.2f,0.6f,1.0f,1.0f //青色
    );
    player.draw(context.modelLoc);

    //-----------------
    // Bullet描画
    //-----------------
    glUniform4f(
        context.colorLocation,
        1.0f, 0.5f, 0.2f, 1.0f  //オレンジ
    );
    bulletManager.draw(context.modelLoc,context.cubeVAO);

    //--------------------
    // ステージ描画
    //--------------------
    stage.draw(context.modelLoc);

    //----------------------
    // エフェクトの描画
    //----------------------

    //爆発エフェクト
    glUniform4f(
        context.colorLocation,
        1.0f,1.0f,0.0f,1.0f //黄色
    );
    explosionManager.draw(context.modelLoc,context.cubeVAO);


}

void StateRenderer::DrawGameOver(const RenderContext& context)
{
    glClearColor(0.3f,0.0f,0.0f,1.0f);

    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
}