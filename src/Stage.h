#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Stage{
public:
    //コンストラクタ
    Stage();

    //描画
    void Draw(GLuint modelLoc);

    //ワールドオブジェクト
    std::vector<glm::vec3> worldObjects;
};