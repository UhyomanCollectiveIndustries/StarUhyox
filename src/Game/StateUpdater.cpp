#include "StateUpdater.h"


void StateUpdater::updateTitle(
    GLFWwindow* window,
    float deltaTime,
    GameStateManager& gameStateManager,
    Timer& timer)
{
    // デモ:エンターキーでplayingステートへ遷移
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        gameStateManager.changeState(GameState::Playing);

        timer.start(10.0f);
    }
}

void StateUpdater::updatePlaying(
    GLFWwindow* window,
    float deltaTime,
    Camera& camera,
    Player& player,
    BulletManager& bulletManager,
    Stage& stage,
    ExplosionManager& explosionManager,
    CollisionManager& collisionManager,
    EventQueue& eventQueue,
    EventBus& eventBus)
{
    //-------------
    // Playerの更新
    //-------------
    player.update(window,deltaTime);

    //---------------
    // Bulletの更新
    //---------------
    // スペースキー押下フラグ
    static bool spacePressedLast = false;

    bool spacePressed = 
        glfwGetKey(window,GLFW_KEY_SPACE)
            == GLFW_PRESS;

    if(spacePressed && !spacePressedLast){
        // プレイヤーの現在位置から正面(-z方向)へ発射
        bulletManager.fire(
            player.transform.position,
            glm::vec3(0.0f,0.0f,-60.f)
        );
    }

    spacePressedLast = spacePressed;

    // 固定タイムステップ(deltaTimeは後に実装)
    bulletManager.update(deltaTime);

    //---------------
    // Cameraの更新
    //---------------
    camera.transform.position = 
        player.transform.position + glm::vec3(0.0f,4.0f,8.0f);

    camera.target =
        player.transform.position + glm::vec3(0.0f,0.0f,-10.0f);

    glm::mat4 view = camera.GetViewMatrix();

    // 透視投影行列:FOV 70°/アスペクト比:800:600/near=0.1,far=100
    //  FOVを広めにして、スピード感を演出
    glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    //--------------------
    // Stageの更新
    //--------------------
    stage.update(deltaTime);

    //---------------------
    // エフェクトの更新
    //---------------------

    // 爆発エフェクト(deltaTimeは後に実装)
    explosionManager.update(deltaTime);

    //-------------
    // 衝突判定
    //-------------
    collisionManager.checkBulletVsStage(
        bulletManager,
        stage,
        eventQueue
    );

    //---------------
    // イベント処理
    //---------------
    for (const auto& e : eventQueue.collisionEvent)
    {
        eventBus.publish(e);
    }
}

void StateUpdater::updateGameOver(
    GLFWwindow* window,
    float deltaTime,
    GameStateManager& gameStateManager)
{
    // デモ:スペースキーでタイトルステートに遷移
    if(glfwGetKey(window,GLFW_KEY_SPACE)
        == GLFW_PRESS)
    {
        gameStateManager.changeState(
            GameState::Title
        );
    }
}