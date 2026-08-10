#pragma once

#include "StageObject.h"
#include "../Graphics/RenderContext.h"

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Stage
{
public:
    Model rockModel;

    // ステージオブジェクト
    std::vector<StageObject> worldObjects;


public:
    // コンストラクタ
    Stage();

    void update(float deltaTime);
    void draw(const RenderContext& context);

private:
    void createStageObject(
        Model* model,
        glm::vec3 position,
        glm::vec3 rotation,
        glm::vec3 scale
    );

};