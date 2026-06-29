#include "Stage.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Stage::Stage()
{
    rockModel.load(
        "assets/models/rock/namaqualand_boulder_03_4k.fbx"
    );

    createStageObject(
        &rockModel,
        {0,0,-20},
        {0,0,0},
        {2,2,2}
    );
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