#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

struct StageObject
{
    //現在位置
    glm::vec3 position;
    
    //生存フラグ
    bool isActive = true;

    //半径
    //  衝突判定で用いる
    float radius = 1.0f;
};


class Stage{
public:
    //ステージオブジェクト
    std::vector<StageObject> worldObjects;

public:
    //コンストラクタ
    Stage();

    //描画
    void draw(GLuint modelLoc);
};