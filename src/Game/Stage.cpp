#include "Stage.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <random>

Stage::Stage()
{
    // 毎回違う配置に
    std::random_device rd;
    std::mt19937 gen(rd());

    // x: -15〜15 / y: -5〜10 / z: -20〜-590(60秒×-10ずつ進む想定の範囲)
    std::uniform_real_distribution<float> distX(-15.0f, 15.0f);
    std::uniform_real_distribution<float> distY(-5.0f, 10.0f);
    std::uniform_real_distribution<float> distZ(-590.0f, -20.0f);

    for (int i = 0; i < 30; ++i)
    {
        glm::vec3 position = {
            distX(gen),
            distY(gen),
            distZ(gen)
        };

        createStageObject(
            &rockModel,
            position,
            {0, 0, 0},
            {2, 2, 2}
        );
    }
}

void Stage::update(float deltaTime)
{
    for(auto& obj : worldObjects)
    {
        if(obj.isActive)
        {
            obj.update(deltaTime);
        }
    }
}

void Stage::draw(GLuint modelLoc)
{

    for(auto& obj : worldObjects)
    {
        if(obj.isActive)
        {
            obj.draw(modelLoc);
        }
    }
}

void Stage::createStageObject(
    Model* model,
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale)
{
    StageObject obj;

    obj.model = model;
    obj.transform.position = position;
    obj.transform.rotation = rotation;
    obj.transform.scale = scale;

    worldObjects.push_back(obj);
}