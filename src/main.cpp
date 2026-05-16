#include "Camera.h"
#include "Player.h"
#include "Stage.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

//===================
// シェーダソース
//===================

//バーテックスシェーダ
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

//シェーダコンパイル関数
unsigned int compileShader(unsigned int type, const char* src){
    //シェーダオブジェクト作成
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader,1,&src,nullptr);
    glCompileShader(shader);

    //コンパイルエラーチェック
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //ウィンドウ作成
    GLFWwindow* window = glfwCreateWindow(800, 600, "StarUhyox", nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //GLAD初期化
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD init failed" << std::endl;
        return -1;
    }

    //深度テストを有効化(奥行判定の実装)
    glEnable(GL_DEPTH_TEST);

    //----------------------
    // シェーダ初期化
    //----------------------

    //シェーダコンパイル
    unsigned int vertShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    unsigned int fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    //シェーダプログラム作成とリンク
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    //UniformLocationの取得
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    //-------------------------
    // メッシュ初期化
    //-------------------------

    //Playerの頂点データ
    float playerVertices[] = {
        //Node
        0.0f,0.0f,-1.0f,

        //Left Wing
        -1.0f,0.0f,1.0f,

        //Right Wing
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

    //-----------------
    // バッファ設定
    //-----------------
    //VAOとVBOの生成と設定

    //PlayerのVAOとVBO
    unsigned int playerVAO;
    unsigned int playerVBO;

    glGenVertexArrays(1,&playerVAO);
    glGenBuffers(1,&playerVBO);

    glBindVertexArray(playerVAO);

    glBindBuffer(GL_ARRAY_BUFFER,playerVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(playerVertices),playerVertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //立方体のVAOとVBO
    unsigned int cubeVAO,cubeVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&cubeVBO);

    //立方体の頂点データをバインド
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //色設定
    int colorLocation = glGetUniformLocation(shaderProgram, "uColor");

    float colors[3][4] = {
        {1.0f, 0.5f, 0.2f, 1.0f},  //オレンジ
        {0.2f, 0.6f, 1.0f, 1.0f},  //青
        {0.2f, 0.9f, 0.4f, 1.0f},  //緑
    };
    int colorIndex = 0;
    //色変更のフラグ(長押しを防ぐために使用)
    bool spaceWasPressed = false;

    //========================
    // ゲームオブジェクト初期化
    //========================

    //カメラの生成
    Camera camera;

    //Playerの生成
    Player player;

    //デモ用のモデル(ワールドに何個か配置)
    Stage stage;

    //==============
    // メインループ
    //==============
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        //=======
        // 更新
        //========

        //スペースキーが押されたら色を切り替える
        bool spaceIsPressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
        if (spaceIsPressed && !spaceWasPressed) {
            colorIndex = (colorIndex + 1) % 3;
        }
        spaceWasPressed = spaceIsPressed;

        //-------------
        // Playerの更新
        //-------------
        player.Update(window);

        //---------------
        // Cameraの更新
        //---------------
        camera.position =
            player.position + glm::vec3(0.0f,4.0f,8.0f);

        camera.target =
            player.position + glm::vec3(0.0f,0.0f,-10.0f);

        glm::mat4 view = camera.GetViewMatrix();

        //透視投影行列(FOV)
        glm::mat4 projection = glm::perspective(
            glm::radians(70.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glUniform4f(colorLocation,
            colors[colorIndex][0],
            colors[colorIndex][1],
            colors[colorIndex][2],
            colors[colorIndex][3]
        );

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

        //======
        // 描画
        //======

        //------------
        // Player描画
        //-----------
        glBindVertexArray(playerVAO);

        player.Draw(modelLoc,playerVAO);

        //--------------------
        // ワールド描画(デモ)
        //--------------------
        glBindVertexArray(cubeVAO);

        stage.Draw(modelLoc);

        //==============
        // Render End
        //==============
        glfwSwapBuffers(window);
    }

    //================
    // Cleanup
    //================
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}