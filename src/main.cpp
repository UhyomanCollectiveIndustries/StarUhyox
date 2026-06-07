#include "Graphics/Camera.h"
#include "Graphics/Model.h"

#include "Game/Player.h"
#include "Game/BulletManager.h"
#include "Game/Stage.h"

#include "Systems/CollisionManager.h"

#include "Core/EventQueue.h"
#include "Core/EventBus.h"
#include "Core/Transform.h"

#include "Systems/DestroySystem.h"
#include "Effects/ExplosionManager.h"
#include "Systems/EffectSystem.h"
#include "Systems/SoundSystem.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <iostream>
#include <vector>

//===================
// シェーダソース
//===================

//バーテックスシェーダ
//  頂点座標をモデル->ワールド->カメラ->クリップ空間へ変換
//  MVP行列(model/view/projection)は毎フレームCPU側からuniformで渡す
const char* vertexShaderSrc = R"(
    #version 330 core

    layout(location = 0) in vec3 aPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main(){
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)";

//フラグメントシェーダ
//  全ピクセルをuniformで渡された単色(uColor)で塗る
//  テクスチャは使わず、描画対象の切り替えはCPU側でのuColor変更で行う
const char* fragmentShaderSrc = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 uColor;
    void main(){
        FragColor = uColor;
    }
)";

//====================
// ユーティリティ関数
//====================

//シェーダをコンパイルしてオブジェクトIDを返す
unsigned int compileShader(unsigned int type, const char* src){
    //シェーダオブジェクト作成
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader,1,&src,nullptr);
    glCompileShader(shader);

    //コンパイルエラーチェック
    //  エラー時はログを表示
    int success;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success){
        char log[512];
        glGetShaderInfoLog(shader,512,nullptr,log);
        std::cerr << "Shader compile error:\n" << log << std::endl;
    }
    return shader;
}

//=========================
// メイン
//=========================
int main() {
    //==================
    // 初期化
    //==================

    //-----------------
    // ライブラリ初期化
    //-----------------

    //GLFW初期化
    glfwInit();
    //OpenGLのバージョンとプロファイルを指定(3.3コアプロファイル)
    //コアプロファイル(非推奨APIを除いたモード)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //ウィンドウ作成
    GLFWwindow* window = glfwCreateWindow(800, 600, "StarUhyox", nullptr, nullptr);
    if (!window) {
        //エラーチェック
        std::cerr << "Window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //GLAD初期化(OpenGL関数ポインタをロード)
    //  glfwGetProcAddress でドライバ固有のポインタを取得するため
    //  glfwMakeContextCurrent より後に呼ぶ必要がある
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD init failed" << std::endl;
        return -1;
    }

    //深度テストを有効化(奥行判定の実装)
    //  有効化にしない場合、後から描画したオブジェクトが手前のオブジェクトの上に重なる
    glEnable(GL_DEPTH_TEST);

    //描画モードフラグ
    bool wireframe = false;
    bool f1PressedLast = false;
    //最初は塗りつぶし
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //----------------------
    // シェーダ初期化
    //----------------------

    //頂点・フラグメントシェーダシェーダコンパイル
    unsigned int vertShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    unsigned int fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    //シェーダプログラム作成とリンク
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    //リンク後は個別シェーダオブジェクトが不要になるため解放
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    //毎フレーム書き換えるUniformLocationを取得
    //  glGetUniformLocationはコストがかかるため、ループ外で一度だけ取得
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    //-------------------------
    // メッシュ初期化
    //-------------------------

    //デモ:Playerの頂点データ
    float playerVertices[] = {
        //機首
        0.0f,0.0f,-1.0f,

        //左翼端
        -1.0f,0.0f,1.0f,

        //右翼端
        1.0f,0.0f,1.0f,
    };

    //立方体の頂点データ(6面×2三角形×3頂点 = 36頂点)
    float vertices[] = {
        // front
        -0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,

        // back
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,

        0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,

        // left
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,

        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        // right
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,

        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        // top
        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,

        // bottom
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,

        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f
    };

    //-----------------------
    // バッファ設定(VAO/VBO)
    //-----------------------
    //VAOとVBOの生成と設定

    //--- Player ---
    //  VAOに頂点フォーマットを記録しておくことで、
    //  描画時はglBindVertexArray(playerVBO)だけで設定を復元できる
    unsigned int playerVAO,playerVBO;

    glGenVertexArrays(1,&playerVAO);
    glGenBuffers(1,&playerVBO);

    glBindVertexArray(playerVAO);

    glBindBuffer(GL_ARRAY_BUFFER,playerVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(playerVertices),playerVertices,GL_STATIC_DRAW);

    //location=0 : position(vec3)
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //--- 立方体 ---
    //  弾とステージは同じキューブ形状を扱う(暫定)ため、VBOを共有
    //  色はフラグメントシェーダのuColor uniformで切り替える
    unsigned int cubeVAO,cubeVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&cubeVBO);

    //立方体の頂点データをバインド
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //色 uniformLocation(描画対象ごとに変更して色を切り替える)
    int colorLocation = glGetUniformLocation(shaderProgram, "uColor");

    //========================
    // ゲームオブジェクト生成
    //========================

    Camera           camera;             //カメラ
    Model            model;              //3Dモデル

    Player           player;             //プレイヤー
    BulletManager    bulletManager;      //弾の一元管理
    Stage            stage;              //ステージ背景オブジェクト

    CollisionManager collisionManager;   //衝突判定の管理

    EventQueue       eventQueue;         //イベントキュー
    EventBus         eventBus;           //イベントバス

    DestroySystem    destroySystem;      //デストロイシステム
    ExplosionManager explosionManager;   //爆発エフェクトの管理
    SoundSystem      soundSystem;        //サウンドシステム

    Transform        transform;

    //エフェクトシステムの初期化(各エフェクトマネージャーを格納)
    EffectSystem effectSystem(
        &explosionManager
    );

    //イベントlistenerの追加
    eventBus.subscribeCollision(
        [&](const CollisionEvent& e){
            destroySystem.OnCollision(e);
            effectSystem.OnCollision(e);
            soundSystem.OnCollision(e);
        }
    );

    //音声ファイルのロード
    soundSystem.LoadSound("boom","assets/sounds/a.wav");

    //クロックの初期化
    double lastTime = glfwGetTime();

    //3Dモデルのロード
    model.load("assets/models/test.fbx");

    //トランスフォームの設定
    transform.position =
    {
        -154.0f,
        -24.0f,
        -20.0f
    };

    transform.rotation =
    {
        0.0f,
        0.0f,
        0.0f
    };

    transform.scale =
    {
        1.0f,
        1.0f,
        1.0f
    };

    std::cout
        << transform.position.x << " "
        << transform.position.y << " "
        << transform.position.z << std::endl;

    std::cout
        << transform.rotation.x << " "
        << transform.rotation.y << " "
        << transform.rotation.z << std::endl;

    std::cout
        << transform.scale.x << " "
        << transform.scale.y << " "
        << transform.scale.z << std::endl;

    //モデルに適応
    glm::mat4 modelMatrix =
        transform.GetMatrix();

    //==============
    // メインループ
    //==============
    while (!glfwWindowShouldClose(window)) {
        //デルタタイム計測
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        //処理が重くなった際、最大でも1/20秒の移動量に制限する
        if(deltaTime > 0.05f){
            deltaTime = 0.05f;
        }

        //OSイベント(ウィンドウ操作・入力など)を処理
        glfwPollEvents();

        //=======
        // 更新
        //========

        //-------------
        // Playerの更新
        //-------------
        player.update(window,deltaTime);

        //---------------
        // Bulletの更新
        //---------------
        //スペースキー押下フラグ
        static bool spacePressedLast = false;

        bool spacePressed = 
            glfwGetKey(window,GLFW_KEY_SPACE)
                == GLFW_PRESS;

        if(spacePressed && !spacePressedLast){
            //プレイヤーの現在位置から正面(-z方向)へ発射
            bulletManager.fire(
                player.position,
                glm::vec3(0.0f,0.0f,-60.f)
            );
        }

        spacePressedLast = spacePressed;

        //固定タイムステップ(deltaTimeは後に実装)
        bulletManager.update(deltaTime);

        //---------------
        // Cameraの更新
        //---------------
        camera.position =
            player.position + glm::vec3(0.0f,4.0f,8.0f);

        camera.target =
            player.position + glm::vec3(0.0f,0.0f,-10.0f);

        glm::mat4 view = camera.GetViewMatrix();

        //透視投影行列:FOV 70°/アスペクト比:800:600/near=0.1,far=100
        //  FOVを広めにして、スピード感を演出
        glm::mat4 projection = glm::perspective(
            glm::radians(70.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );

        //---------------------
        // エフェクトの更新
        //---------------------

        //爆発エフェクト(deltaTimeは後に実装)
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


        //======
        // 描画
        //======

        //カラーバッファのクリア
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //背景を青緑色に指定
        //深度バッファのクリア
        //  クリアしないと、前フレームの深度値が残り、正しい前後関係が判定できない
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        //view/projectionはフレーム内で共通のため一度だけ送信
        glUniformMatrix4fv(
            viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );
        glUniformMatrix4fv(
            projectionLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        //F1キーで描画モードの切り替え
        bool f1Pressed =
            glfwGetKey(window,GLFW_KEY_F1) == GLFW_PRESS;

        if(f1Pressed && !f1PressedLast)
        {
            wireframe = !wireframe;

            if(wireframe)
            {
                std::cout << "Wireframe ON" << std::endl;
            }
            else
            {
                std::cout << "Wireframe OFF" << std::endl;
            }
        }
        
        f1PressedLast = f1Pressed;
        if (wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        //-------------
        // 3Dモデル描画
        //-------------

        glUniformMatrix4fv(
            modelLoc,
            1,
            GL_FALSE,
            glm::value_ptr(modelMatrix)
        );

        glDisable(GL_CULL_FACE);

        model.draw();

        //------------
        // Player描画
        //-----------
        glUniform4f(
            colorLocation,
            0.2f,0.6f,1.0f,1.0f //青色
        );
        player.draw(modelLoc,playerVAO);

        //-----------------
        // Bullet描画
        //-----------------
        glUniform4f(
            colorLocation,
            1.0f, 0.5f, 0.2f, 1.0f  //オレンジ
        );
        bulletManager.draw(modelLoc,cubeVAO);

        //--------------------
        // ステージ描画
        //--------------------
        glUniform4f(
            colorLocation,
            0.2f,0.9f,0.4f,1.0f //緑色
        );
        glBindVertexArray(cubeVAO);
        stage.draw(modelLoc);

        //----------------------
        // エフェクトの描画
        //----------------------

        //爆発エフェクト
        glUniform4f(
            colorLocation,
            1.0f,1.0f,0.0f,1.0f //黄色
        );
        explosionManager.draw(modelLoc,cubeVAO);

        //======================
        // イベントキューのクリア
        //======================
        eventQueue.Clear();

        //======================
        // ダブルバッファリング
        //======================
        //フロントとバックを入れ替えて画面に表示
        glfwSwapBuffers(window);
    }

    //==========
    // 終了処理
    //==========
    //GPUリソースを明示的に解放(アプリ終了時にもOSが自動的に回収する)
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}