#include "GameObject.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <iostream>

void GameObject::update(float deltaTime)
{

}

void GameObject::draw(
    unsigned int modelLoc
)
{
    
    if(model == nullptr)
    {
        return;
    }

    glm::mat4 modelMatrix =
        transform.GetMatrix()
        * modelTransform.GetMatrix();

    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(modelMatrix)
    );

    model -> draw();
}

void GameObject::setModel(Model* model)
{
    this->model = model;
}