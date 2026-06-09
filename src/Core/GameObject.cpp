#include "GameObject.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

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

    glm::mat4 matrix =
        transform.GetMatrix();

    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(matrix)
    );

    model -> draw();
}