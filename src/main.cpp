#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Player.h"


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

int main() {
    //GLFWの初期化
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

    //GLADの初期化
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD init failed" << std::endl;
        return -1;
    }

    //深度テストを有効化(奥行判定の実装)
    glEnable(GL_DEPTH_TEST);


    //----------------
    // シェーダプログラム
    //----------------

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

    //-------------
    // 頂点データとバッファ設定
    //-------------

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

    //VAOとVBOの生成と設定
    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    int colorLocation = glGetUniformLocation(shaderProgram, "uColor");

    float colors[3][4] = {
        {1.0f, 0.5f, 0.2f, 1.0f},  // orange
        {0.2f, 0.6f, 1.0f, 1.0f},  // blue
        {0.2f, 0.9f, 0.4f, 1.0f},  // green
    };
    int colorIndex = 0;

    bool spaceWasPressed = false;

    //カメラ移動変数
    //カメラ位置
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    //カメラの前方向
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    //カメラの上方向
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


    //Playerの生成
    Player player;

    //デモ用のモデル
    std::vector<glm::vec3> worldObjects;

    for (int z = 0; z > -100; z -= 5)
    {
        worldObjects.push_back(glm::vec3(-3.0f, 0.0f, (float)z));
        worldObjects.push_back(glm::vec3( 3.0f, 0.0f, (float)z));
    }

    //-------------
    // メインループ
    //-------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        //更新
        player.Update(window);

        //スペースキーが押されたら色を切り替える
        bool spaceIsPressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
        if (spaceIsPressed && !spaceWasPressed) {
            colorIndex = (colorIndex + 1) % 3;
        }
        spaceWasPressed = spaceIsPressed;

        //モデル行列の作成
        glm::mat4 model = glm::translate(
            glm::mat4(1.0),
            player.position
        );

        // //モデル行列に回転
        // model = glm::rotate(
        //     model,
        //     (float)glfwGetTime(),
        //     glm::vec3(0.0f, 1.0f, 0.0f)
        // );

        //モデル行列に拡大縮小
        model = glm::scale(
            model,
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        glm::vec3 cameraOffset = glm::vec3(0.0f,2.0f,6.0f);
        cameraPos = player.position + cameraOffset;

        // cameraPos = glm::mix(
        //     cameraPos,
        //     targetPos,
        //     deltaTime * 5.0f
        // );

        //カメラ位置
        glm::mat4 view = glm::lookAt(
            cameraPos,
            //cameraPos + cameraFront,    //カメラがどこを向いているか
            player.position + glm::vec3(0.0f,0.0f,-10.0f),
            cameraUp
        );

        // //カメラ入力処理
        // float cameraSpeed = 0.01f;

        // //カメラの前後入力
        // if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //     cameraPos += cameraSpeed * cameraFront;
        
        // if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //     cameraPos -= cameraSpeed * cameraFront;

        // // 将来的なカメラの実装(自機を追従させる方式)
        // // cameraPos = lerp(
        // //     cameraPos,
        // //     targetPos,
        // //     deltaTime * followSpeed
        // // );

        // //カメラの左右入力
        // //  cross(外積)で右方向ベクトルを作成   
        // //  normalizeで長さ1へ正規化(方向ベクトルにする)
        // glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

        // if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        //     cameraPos -= cameraRight * cameraSpeed;
        
        // if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //     cameraPos += cameraRight * cameraSpeed;

        //透視投影行列
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
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
            modelLoc,
            1,
            GL_FALSE,
            glm::value_ptr(model)
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

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //ワールドスペースに立方体を配置
        for (const auto& pos : worldObjects)
        {
            glm::mat4 model = glm::translate(
                glm::mat4(1.0f),
                pos
            );

            glUniformMatrix4fv(
                modelLoc,
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}